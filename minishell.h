/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 13:29:59 by yabounna          #+#    #+#             */
/*   Updated: 2025/08/24 16:15:31 by arahhab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "parsing/ft_malloc/ft_malloc.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "execution/execution.h"
# include <termios.h>

# define PATHD "/bin/:/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:"

extern int	g_handl_signals;

typedef enum s_type_token
{
	WORD,
	PIPE,
	RDR_IN,
	RDR_OUT,
	APPEND,
	HERE_DOC
}	t_type_token;

typedef struct s_token
{
	char			*value;
	t_type_token	type;
	int				quoted;
	int				double_quote;
	int				join;
	struct s_token	*next;
}	t_token;

typedef struct s_file
{
	int				type;
	char			*file_name;
	int				fd;
	struct s_file	*next;
}	t_file;

typedef struct s_exec
{
	char			**cmd;
	t_file			*files;
	struct s_exec	*next;
}	t_exec;

typedef struct s_garbage
{
	void				*ptr;
	struct s_garbage	*next;
}	t_garbage;

typedef struct s_parsing_context
{
	const char		*line;
	int				*index;
	int				quoted_flag;
	t_garbage		**garb;
}	t_parsing_context;

typedef struct s_list_env
{
	void				*variable;
	void				*val;
	struct s_list_env	*next;
}	t_list_env;

typedef struct s_expand_ctx
{
	t_list_env		*env;
	int				exit_code;
	t_garbage		**garb;
}	t_expand_ctx;

typedef struct s_ctx
{
	t_list_env		*env;
	t_garbage		**garb;
	char			**tmp;
}	t_ctx;

typedef struct s_expand_ctx_heredoc
{
	t_list_env		*env;
	t_garbage		**garb;
	char			**tmp;
}	t_expand_ctx_heredoc;

typedef struct s_heredoc_ctx
{
	int				expand;
	t_list_env		*env;
	t_garbage		**garb;
	int				fd;
}	t_heredoc_ctx;

typedef struct s_fill_ctx
{
	t_exec		*new_cmd;
	t_file		***current;
	t_token		**tokens;
	int			i;
	t_garbage	**garb;
}	t_fill_ctx;

typedef struct s_read_loop
{
	char				*line;
	t_garbage			*garb;
	t_token				*token;
	int					last_exit_code;
	t_list_env			*env;
	t_parsing_context	ctx;
	int					i;
	int					flag_path;
}	t_read_loop;

typedef struct s_inf_expand_red
{
	int		i;
	char	*res;
	char	*tmp;
	char	*content;
}	t_inf_expand_red;

t_type_token	get_token_type(char *str);

int				syntaxe_errors(char *args);
int				error_quote(char *caracter, int *i);
int				error_pipe(char *caracter, int *i);
int				error_redir(char *str, int *i);

t_token			*tokens(const char *line, t_garbage **garb,
					t_parsing_context *ctx);
void			handel_quote(const char *line, int *i,
					t_token **token, t_garbage **garb);
void			handel_double_operator(const char *line, int *i,
					t_token **tokens, t_garbage **garb);
void			handle_single_operator(const char *line, int *i,
					t_token **tokens, t_garbage **garb);
void			handle_word(t_parsing_context *ctx, t_token **tokens);
void			add_token(t_token **list, t_token *new_tok);
t_token			*new_token_0(char *value, t_type_token type,
					t_garbage **garb);
t_token			*new_token(char *value, t_type_token type, int i,
					t_garbage **garb);

void			expand_all_tokens(t_token **tokens, int exit_code,
					t_list_env *env, t_parsing_context ctx);
char			*expand_token(char *value, int exit_code,
					t_list_env *env, t_garbage **garb);
char			*expand_dollar(char *value, int *i, t_expand_ctx *ctx);
void			append_double_quote(const char *val, int *i,
					char **res, t_expand_ctx ctx);
void			append_single_quote(const char *val, int *i,
					char **res, t_garbage **garb);
char			*get_env_value(char *name, t_list_env *env, t_garbage **garb);
void			replace_token(t_token **head, t_token *old, t_token *new_list);
t_token			*get_last_token(t_token *tokens);
void			add_token_back(t_token **head, t_token *new_token);
int				is_valid_var_char(char c);
char			*ft_strtrim_custom(char *str, t_garbage **garb, int quoted);
t_token			*split_tokens_by_space(char *str, t_garbage **garb,
					t_type_token type);
int				should_expand(t_token *curr, t_parsing_context ctx,
					t_token *prev);
t_token			*handle_expanded_tokens(t_token **tokens, t_token *curr,
					t_expand_ctx *ctx1, t_parsing_context ctx);
t_token			*update_curr_after_expand(t_token **tokens,
					t_token *curr, t_expand_ctx *ctx1, t_parsing_context ctx);

char			**extract_cmd_from_tokens(t_token *tokens, t_garbage **garb);
void			free_exec_list(t_exec *exec_list);
int				is_redirection(t_type_token type);
t_file			*extract_redirs_from_tokens(t_token *tokens, t_garbage **garb);
t_exec			*parse_tokens_to_exec_list(t_token *tokens, t_garbage **garb);
t_exec			*init_new_cmd(t_garbage **garb, int count);

int				ft_isalnum(int c);
int				ft_isalpha(int c);
char			*ft_itoa(int n, t_garbage **garb);
void			*ft_memcpy(void *dst, const void *src, size_t n);
char			**ft_split(const char *s, char c, t_garbage **garb);
char			*ft_strchr(const char *s, int c);
int				ft_strcmp(const char *s1, const char *s2);
char			*ft_strdup(const char *s1, t_garbage **garb);
char			*ft_strjoin(char const *s1, char const *s2, t_garbage **garb);
char			*ft_strtrim(char const *s1, char const *set, t_garbage **garb);
char			*ft_substr(char const *s, unsigned int start, size_t len,
					t_garbage **garb);
int				skip_space(char c);
int				is_quote(char c);
int				is_operator(char c);
int				redirection(char c);
void			space_skip(const char *line, int *i);
size_t			ft_strlen(const char *s);
int				if_only_space(char *str);

void			setup_signals(void);
void			handle_sigint(int sig);

void			process_heredocs(char *line, t_exec *exec,
					t_list_env *env, t_garbage **garb);
int				heredoc_expand(char *line, t_list_env *env,
					t_garbage **garb, char **res);
int				create_heredoc(char *delimiter, int expand,
					t_list_env *env, t_garbage **garb);
int				append_normal_char(char **tmp, char c, t_garbage **garb);
int				append_raw_dollar(char **tmp, char c, t_garbage **garb);
int				append_variable(char *line, t_list_env *env,
					t_garbage **garb, char **tmp);
int				append_exit_status(char **tmp, t_garbage **garb);
int				heredoc_expansion(char *line, t_list_env *env,
					t_garbage **garb, char **res);
void			append_char(char **tmp, char c, t_garbage **garb);

void			save_terminal_settings(void);
void			restore_terminal_settings(void);
int				ft_exit_status(int status, int flag);

void			norm_read_loop(t_exec **data, t_read_loop	inf_read);
int				check_exist_path(t_list_env *env);
void			add_path(t_read_loop *inf_read);
char			*expand_red(char *value, t_expand_ctx *ctx, t_garbage **garb);
t_token			*check_if_red(t_token *curr, t_garbage **garb,
					t_expand_ctx ctx1);
void			ft_readline(t_read_loop *inf_read);
#endif