/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 23:19:57 by arahhab           #+#    #+#             */
/*   Updated: 2025/08/21 15:27:26 by arahhab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "../minishell.h"
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <errno.h>

typedef struct s_list_env	t_list_env;
typedef struct s_exec		t_exec;
typedef struct s_garbage	t_garbage;
typedef struct s_read_loop	t_read_loop;

typedef struct s_cd
{
	char		*old_pwd;
	char		*new_pwd;
	t_garbage	**garb;
}	t_cd;

typedef struct s_exit
{
	int	c_cmd;
	int	len;
	int	argc;
}	t_exit;

typedef struct s_export
{
	int		i;
	int		j;
	int		c;
	char	**arg_ex;
	int		error;
}	t_export;

typedef struct s_info_pipe
{
	int			i;
	int			pid;
	int			fd[2];
	int			in_fd;
	char		*path_cmd;
	int			in_bultin;
	int			j;
	char		**tab_envv;
	int			count_cmd;
	int			status;
	struct stat	info;
}	t_info_pipe;

typedef struct s_inf_cher_path
{
	char	*path;
	int		c_cmd;
}	t_inf_cher_path;

void		ft_put_string(char *str);
int			ft_strcmpp(const char *s1, const char *s2);
char		**ft_splitt(char const *s, char c, t_garbage **garb);
void		*ft_memcpyy(void *dst, const void *src, size_t n);
t_list_env	*ft_envvv(char **str, t_garbage **garb);
int			ft_strlen_argc(char **str);
int			ft_strlenn(char *str);
void		ft_cd(char **args, t_list_env *env, t_garbage **garb);
void		ft_echo(char **str);
void		ft_exit(t_exit inf_exit, char **str, t_garbage **garb);
void		lst_add_back(t_list_env **lst, t_list_env *new);
t_list_env	*ft_lstnew(void *variable, void *val, t_garbage **garb);
void		ft_print_env(t_list_env *env, t_read_loop *inf_read);
void		ft_export(t_list_env *list_env, char **args, t_read_loop *inf_read);
char		*ft_pwd(t_list_env *env, t_garbage **garb);
void		ft_unset(t_list_env **list_env, char **args);
void		ft_print_env_ex(t_list_env *env, t_read_loop *inf_read);
void		ft_supp_arg(t_list_env **list_env, char *arg);
char		*ft_concat(char *str, char *str2, t_garbage **garb);
char		*cherch_path(t_list_env **env, t_exec *data,
				int count_cmd, t_garbage **garb);
int			ft_built_in(t_exec *data, t_list_env **env, int count_cmd,
				t_read_loop *inf_read);
void		ft_pipe(t_exec *data, t_list_env **env, t_read_loop *inf_read);
char		*ft_cherch_home(t_list_env *env);
int			verif_exist(t_list_env **list_env, char *arg);
void		chng_el(t_list_env **list_env, t_export indx, t_garbage **garb);
void		error_export(char **args, int i, int *error);
void		ft_redirection(t_exec *data, t_garbage **garb);
int			ft_count_env(t_list_env *env);
char		**tab_env(t_list_env *env, t_garbage **garb);
int			is_slash(char *str);
int			count_cmd(t_exec *data);
int			is_built_in(char *str);
int			is_espace_tabulion(char *cmd);
int			ft_count_cmd(t_exec *data);
int			check_home(t_list_env *env);
void		error_exit(char *str, int count_cmd, t_garbage **garb);
void		error_exit2(int count_cmd);
int			modulo(unsigned long long number);
void		ft_input(int *fd, char *file_name);
void		ft_output(int *fd, char *file_name, struct stat info);
void		ft_output_append(int *fd, char *file_name);
void		ft_herdoc(int *fd);
int			ft_isalnumm(int c);
int			ft_isalphaa(int c);
void		ft_error_pipe(t_exec *data, t_garbage **garb);
void		ft_error_pipe2(t_exec *data, t_info_pipe inf_pip, t_garbage **garb);
void		ft_error_fork(void);
void		ft_wait_child(t_info_pipe *inf_pip);
void		error_cherch_path(char *cmd, t_garbage **garb);
char		*new_str(char *str);
int			norm_help_built(t_list_env **env, char **cmd);
int			norm_check_arg(char **args, t_export *ix);
int			norm_check_arg2(char **args, t_export *ix);
void		norm_exp_el_h(char *args, t_export *indx, t_garbage **garb);
int			check_exist_pwd(t_list_env *env);
void		ft_change_oldpwd(t_list_env **env);
void		norm_ft_exec_child(char *cmd, t_garbage **garb);
void		ft_check_signals(int *status);
void		ft_status(t_exec *data, int *status);
void		change_flag_path(t_read_loop *inf_read, t_export indx);
int			check_name(char *str, t_garbage **garb);
#endif