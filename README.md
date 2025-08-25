# 🐚 Minishell – Projet 42

> Recréez un mini-interpréteur de commandes en C, avec gestion des pipes, redirections, variables d’environnement et signaux – comme un vrai petit Bash !

---

## 📌 Sommaire

- [🎯 Objectif](#-objectif)
- [⚙️ Fonctionnalités](#️-fonctionnalités)
- [✨ Bonus](#-bonus)
- [📦 Compilation](#-compilation)
- [🧠 Utilisation](#-utilisation)
- [🧪 Tests](#-tests)
- [📚 Normes respectées](#-normes-respectées)
- [👨‍💻 Auteurs](#-auteurs)

---

## 🎯 Objectif

Le but du projet **Minishell** est de recréer un shell UNIX minimaliste en langage **C**, en respectant le comportement du shell Bash sur un ensemble de fonctionnalités.  
Cela implique la gestion de la **lecture d’entrées utilisateur**, du **parsing**, de l’**exécution de commandes**, de la **redirection**, de la **gestion de signaux** et de l’**environnement système**.

---

## ⚙️ Fonctionnalités

Le projet implémente les fonctionnalités suivantes :

✅ Lecture d’une ligne de commande via `readline()`  
✅ Parsing des commandes et des arguments  
✅ Gestion des quotes simples `'` et doubles `"`  
✅ Expansion des variables d’environnement (`$HOME`, `$?`, etc.)  
✅ Exécution de commandes simples (ex: `ls`, `echo`, `pwd`, …)  
✅ Gestion des chemins via `$PATH`  
✅ Gestion des erreurs (commandes inexistantes, erreurs de syntaxe, etc.)  
✅ Gestion des redirections :
  - `>` redirection de sortie
  - `<` redirection d’entrée
  - `>>` redirection de sortie en append
✅ Gestion des pipes (`|`)  
✅ Gestion des signaux :
  - `CTRL+C` → affiche une nouvelle ligne
  - `CTRL+D` → quitte le shell proprement
  - `CTRL+\` → ignoré

✅ Implémentation des builtins suivants :
- `echo` (avec `-n`)
- `cd`
- `pwd`
- `export`
- `unset`
- `env`
- `exit`

---

## ✨ Bonus

Les bonus implémentés sont :

🎯 **Gestion des redirections combinées avec pipes**  
🎯 **Gestion des heredocs** (`<<`)  
🎯 **Gestion des quotes dans les heredocs**  
🎯 **Support des variables d’environnement dans les heredocs (si non quoted)**  
🎯 **Exécution de plusieurs pipes enchaînés (`cmd1 | cmd2 | cmd3`)**  
🎯 **Gestion des erreurs de syntaxe avancée**  
🎯 **Gestion du comportement de Bash pour `$?`, quotes, expansions complexes, etc.**  
🎯 **Garbage collector personnalisé pour éviter les fuites mémoire**

---

## 📦 Compilation

Le projet est compilé avec `make`.

```bash
make        # compile minishell
make clean  # supprime les .o
make fclean # supprime les .o + l'exécutable
make re     # recompile tout
