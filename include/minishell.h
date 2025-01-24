/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:06:16 by jlecorne          #+#    #+#             */
/*   Updated: 2025/01/24 16:28:57 by jlecorne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* Types de tokens */
# define CMD 0
# define ARG 1
# define VAR 2
# define OPTION 3
# define BUILTIN 4
# define DECLAVAR 5
# define PIPE 6
# define INPUT 7
# define OUTPUT 8
# define APPEND 9
# define HEREDOC 10

# include "../libft/include/libft.h"
# include <curses.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

/* Variable Globale pour les signaux */
int					g_sig;

/* Structure des tokens pour parsing de l'input */
typedef struct s_token
{
    char            *s;    	// Token string
    int             idx;   	// Token index
    int             type;  	// Token type
    struct s_token *prev;  	// Token précédent dans la liste chainée
    struct s_token *next;  	// Prochain Token dans la liste chainée
}					t_token;

/* Structure principale du shell et informations au runtime */
typedef struct s_shell
{
	t_token *token;  	// Pointeur vers la liste des tokens
    pid_t   *pid;    	// Tableau des process ID
    char    **env;   	// Variables d'environnement
    char    **paths;	// Chemins des exécutables
    char    **args;  	// Arguments de la commande
    char    *line;   	// Ligne de commande saisie par l'utilisateur
    char    *cmd;    	// Commande à exécuter
    char    *home;   	// Chemin du répertoire personnel (home)
    int     **tab;   	// Tableau des file descriptors (child process)
    int     **htab;  	// Tableau pour les here-documents
    int     o_in;    	// Input standard d'origine
    int     o_out;   	// Output standard d'origine
    int     in;      	// Input file descriptor
    int     out;     	// Output file descriptor
    int     ncmd;    	// Nombre de commandes
    int     rtn;     	// Valeur de retour
    int     exit;    	// Exit status
}					t_shell;

/* ************************************************************************** */
/*                                  BUILTINS                                  */
/* ************************************************************************** */
/* Processus principal des builtins */
void				b_process(t_shell *mini, t_token *tk);

/* Utils */
int					tab_lines(char **tab);
int					is_there_an_equal(char *s);
int					max_len(int s1, int s2);
int					check_nb_args(t_token *tk, int i);

/* Builtin CD */
void				b_cd(t_shell *mini, t_token *list);
char				*folder2(t_shell *mini, t_token *list);
char				*folder1(t_shell *mini);
int					valid_path(t_shell *mini, char *tmp_path);
void				test_access(t_shell *mini);
void				modify_pwd_and_tmp(t_shell *mini, char *tmp);
void				modify_pwd(t_shell *mini, t_token *list);
char				*modify_oldpwd(t_shell *mini, char *tmp_pwd);
void				check_var_status(t_shell *mini, t_token *list, char *tmp_path, char *cur_dir);

/* Builtin ECHO */
void				b_echo(t_shell *mini, t_token *list);
int					check_opt(t_token *list, int nb_opt);

/* Builtin ENV */
void				b_env(t_shell *mini, t_token *list);

/* Builtin EXIT */
void				b_exit(t_shell *mini, t_token *list);
void				exit_until(t_shell *mini);
void				exit_too_much(t_shell *mini);

/* Builtin EXPORT */
void				b_export_args(t_shell *mini, t_token *list, int nb_args);
void				b_export(t_shell *mini, t_token *list);
void				print_listed_env(t_shell *mini);
char				**add_var_env(t_shell *mini, int lines, t_token *new);
void				sub_var_env(t_shell *mini, int lines, t_token *sub);
void				sub_var_last_cmd(t_shell *mini);

/* Builtin PWD */
void				b_pwd(t_shell *mini);

/* Builtin UNSET */
void				b_unset(t_shell *mini, t_token *list);


/* ************************************************************************** */
/*                                   UTILS                                    */
/* ************************************************************************** */
/* Gestion de l'environnement */
int					get_shlvl(char *str);
void				alloc_env(t_shell *mini, char **env);
int					check_last(t_shell *mini, char **env, int i);
int					check_shlvl(t_shell *mini, char **env, int i);
int					check_oldpwd(t_shell *mini, char **env, int i);

/* Gestion mémoire */
void				ft_exit_plus(t_shell *mini, char *err, int rtn);
void				ft_exit_all(t_shell *mini, int histo, int rtn);
void				free_str(char *tmp);
void				free_tab(char **tab);
void				free_env(t_shell *mini);
void				free2(char *one, char *two);

/* Gestion historique */
int					create_history(int *histo);
void				add_histo(char *str, int histo);

/* Signaux */
void				define_last(t_shell *mini);
void				define_signals(void);
void				sigint_forked(void);
void				sigquit_forked(void);
void				signal_forked(t_token *tk);
void				sigint_piped(int sig);
void				sigquit_piped(int sig);
void				piped_sig(void);
void				signals_hrdc(void);
void				replace_sig(void);

/* Variables d'environnement */
char				*var_content(t_shell *mini, char *str);
char				*return_var_content(t_shell *mini, char *var);
char				*var_name(t_shell *mini, char *str);
char				*return_var_name(t_shell *mini, char *var);
int					existing_var(t_shell *mini, char *var);


/* ************************************************************************** */
/*                                  PARSING                                  */
/* ************************************************************************** */
char				**custom_split(const char *s, char c, int sw);
char				**tabfree(char **p);
int					scount(const char *s, char c, int q);
void				parse_input(t_shell *mini);
char				*clean_s(char *s);
int					str_alloc(char *s, int *idx);
int					is_dollar(t_token *tk);
int					quote_state(char *line, int idx);
int					is_sep(char *line, int i);
int					is_quote(char *s);
void				convert_var(t_shell *mini, t_token *tk);
char				*get_vname(char *s, int idx);
int					contain_var(char *s);
char				*rewrite(t_shell *mini, char *s, char *vname, int idx);
char				*get_nvar(t_shell *mini, char *vname);
char				*get_ns(char *s, char *nvar, int idx, int vname_len);
char				*other_variable(t_shell *mini, t_token *tmp, int i);
char				*get_other_var(char *vname);
char				*rewrite2(char *s, char *iter, int idx);
void				space(char *line, int *i);
void				token_idx(t_shell *mini);
void				clean_tokens(t_token *tk);
void				*get_token(char *line);
void				post_tk_type(t_token *tk);
void				tk_type(t_token *token);
int					parse_err(t_shell *mini, t_token *tk, int err);
int					syntax_check(t_shell *mini);


/* ************************************************************************** */
/*                                   EXEC                                    */
/* ************************************************************************** */
void				minishell(t_shell *mini);
void				get_args(t_shell *mini, t_token *tk);
void				get_paths(t_shell *mini);
char				**args_alloc(t_token *tk);
char				*get_cmd(t_shell *mini);
int					nb_cmd(t_shell *mini);
t_token				*find_cmd(t_token *tk);
t_token				*next_cmd(t_token *tk);
t_token				*prev_cmd(t_token *tk);
t_token				*next_pipe(t_token *tk);
int					get_htab(t_shell *mini, int i);
void				close_pipes(t_shell *mini, t_token *tk, int i, int sw);
void				close_redir(t_shell *mini, t_token *tk);
void				close_output(t_token *cp, t_token *cur);
void				mini_free(t_shell *mini);
void				pipe_alloc(t_shell *mini);
void				free_token(t_shell *mini);
void				free_paths(t_shell *mini);
void				free_htab(t_shell *mini);
void				free_args(t_shell *mini);
void				free_pipe(t_shell *mini);
void				hrdc_filler(t_shell *mini, t_token *cur, int i);
void				hrdc_manager(t_shell *mini);
void				alloc_htab(t_shell *mini, int nb);
char				*hrdc_convert(t_shell *mini, char *s);
t_token				*next_hrdc(t_token *tk, int i);
void				close_hrdc(t_shell *mini, int cur, int sw);
int					nb_hrdc(t_shell *mini);
int					is_hrdc(t_token *tk);
void				redir(t_shell *mini, t_token *tk, int i);
void				redir_close(t_shell *mini, t_token *tk);
void				args_redir(t_shell *mini, t_token *tk);
int					is_redir(t_token *tk, int mode);
void				err_manager(t_shell *mini, t_token *tk, int err);
void				fds_err(t_shell *mini, char *fname);

#endif