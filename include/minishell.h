/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:06:16 by jlecorne          #+#    #+#             */
/*   Updated: 2023/09/25 15:46:27 by jlecorne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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

int					g_sig;

typedef struct s_token
{
	char			*s;
	int				idx;
	int				type;
	struct s_token	*prev;
	struct s_token	*next;
}					t_token;

typedef struct s_shell
{
	t_token			*token;
	pid_t			*pid;
	char			**env;
	char			**paths;
	char			**args;
	char			*line;
	char			*cmd;
	char			*home;
	int				**tab;
	int				**htab;
	int				o_in;
	int				o_out;
	int				in;
	int				out;
	int				ncmd;
	int				rtn;
	int				exit;
}					t_shell;

/*
BUILTIN
*/
/* b_process */
void				b_process(t_shell *mini, t_token *tk);

/* b_utils */
int					tab_lines(char **tab);
int					is_there_an_equal(char *s);
int					max_len(int s1, int s2);
int					check_nb_args(t_token *tk, int i);

/* b_cd */
void				b_cd(t_shell *mini, t_token *list);

/* b_cd_more */
char				*folder2(t_shell *mini, t_token *list);
char				*folder1(t_shell *mini);
int					valid_path(t_shell *mini, char *tmp_path);
void				test_access(t_shell *mini);

/* b_cd_exce */
void				modify_pwd_and_tmp(t_shell *mini, char *tmp);
void				modify_pwd(t_shell *mini, t_token *list);
char				*modify_oldpwd(t_shell *mini, char *tmp_pwd);
void				check_var_status(t_shell *mini, t_token *list,
						char *tmp_path, char *cur_dir);

/* b_echo */
void				b_echo(t_shell *mini, t_token *list);

/* b_echo_more */
int					check_opt(t_token *list, int nb_opt);

/* b_env */
void				b_env(t_shell *mini, t_token *list);

/* b_exit */
void				b_exit(t_shell *mini, t_token *list);

/* b_exit_more */
void				exit_until(t_shell *mini);
void				exit_too_much(t_shell *mini);

/*	b_export	*/
void				b_export_args(t_shell *mini, t_token *list, int nb_args);
void				b_export(t_shell *mini, t_token *list);

/*	b_export_print	*/
void				print_listed_env(t_shell *mini);

/*	b_export_arg	*/
char				**add_var_env(t_shell *mini, int lines, t_token *new);
void				sub_var_env(t_shell *mini, int lines, t_token *sub);

/* b_var.c */
void				sub_var_last_cmd(t_shell *mini);

/*	b_pwd	*/
void				b_pwd(t_shell *mini);

/*	b_unset	*/
void				b_unset(t_shell *mini, t_token *list);

/*
UTILS
*/
/* u_create_env */
int					get_shlvl(char *str);
void				alloc_env(t_shell *mini, char **env);

/* u_env_excepts */
int					check_last(t_shell *mini, char **env, int i);
int					check_shlvl(t_shell *mini, char **env, int i);
int					check_oldpwd(t_shell *mini, char **env, int i);

/* u_exit */
void				ft_exit_plus(t_shell *mini, char *err, int rtn);
void				ft_exit_all(t_shell *mini, int histo, int rtn);

/*	u_free	*/
void				free_str(char *tmp);
void				free_tab(char **tab);
void				free_env(t_shell *mini);
void				free2(char *one, char *two);

/* u_history */
int					create_history(int *histo);
void				add_histo(char *str, int histo);

/* u_sig*/
void				define_last(t_shell *mini);
void				define_signals(void);

/* u_sig_forked */
void				sigint_forked(void);
void				sigquit_forked(void);
void				signal_forked(t_token *tk);

/* u_sig_piped */
void				sigint_piped(int sig);
void				sigquit_piped(int sig);
void				piped_sig(void);

/* u_sig_hrdc */
void				signals_hrdc(void);
void				replace_sig(void);

/* u_utils */
char				*var_content(t_shell *mini, char *str);
char				*return_var_content(t_shell *mini, char *var);
char				*var_name(t_shell *mini, char *str);
char				*return_var_name(t_shell *mini, char *var);
int					existing_var(t_shell *mini, char *var);

/*
PARSING
*/
/* split */
char				**custom_split(const char *s, char c, int sw);
char				**tabfree(char **p);
int					scount(const char *s, char c, int q);

/* input.c */
void				parse_input(t_shell *mini);

/* utils */
char				*clean_s(char *s);
int					str_alloc(char *s, int *idx);
int					is_dollar(t_token *tk);

/* utils1 */
int					quote_state(char *line, int idx);
int					is_sep(char *line, int i);
int					is_quote(char *s);

/* var.c */
void				convert_var(t_shell *mini, t_token *tk);
char				*get_vname(char *s, int idx);
int					contain_var(char *s);

/* var1.c */
char				*rewrite(t_shell *mini, char *s, char *vname, int idx);
char				*get_nvar(t_shell *mini, char *vname);
char				*get_ns(char *s, char *nvar, int idx, int vname_len);

/* var2.c */
char				*other_variable(t_shell *mini, t_token *tmp, int i);
char				*get_other_var(char *vname);
char				*rewrite2(char *s, char *iter, int idx);

/* token.c */
void				space(char *line, int *i);
void				token_idx(t_shell *mini);
void				clean_tokens(t_token *tk);
void				*get_token(char *line);

/* type.c */
void				post_tk_type(t_token *tk);
void				tk_type(t_token *token);

/* error.c */
int					parse_err(t_shell *mini, t_token *tk, int err);
int					syntax_check(t_shell *mini);

/*
EXEC
*/
/* minishell.c */
void				minishell(t_shell *mini);

/* utils.c */
void				get_args(t_shell *mini, t_token *tk);
void				get_paths(t_shell *mini);
char				**args_alloc(t_token *tk);
char				*get_cmd(t_shell *mini);
int					nb_cmd(t_shell *mini);

/* utils1.c */
t_token				*find_cmd(t_token *tk);
t_token				*next_cmd(t_token *tk);
t_token				*prev_cmd(t_token *tk);
t_token				*next_pipe(t_token *tk);
int					get_htab(t_shell *mini, int i);

/* mem.c */
void				close_pipes(t_shell *mini, t_token *tk, int i, int sw);
void				close_redir(t_shell *mini, t_token *tk);
void				close_output(t_token *cp, t_token *cur);
void				mini_free(t_shell *mini);
void				pipe_alloc(t_shell *mini);

/* free.c */
void				free_token(t_shell *mini);
void				free_paths(t_shell *mini);
void				free_htab(t_shell *mini);
void				free_args(t_shell *mini);
void				free_pipe(t_shell *mini);

/* hrdc.c */
void				hrdc_filler(t_shell *mini, t_token *cur, int i);
void				hrdc_manager(t_shell *mini);
void				alloc_htab(t_shell *mini, int nb);
char				*hrdc_convert(t_shell *mini, char *s);

/* hrdc_u.c */
t_token				*next_hrdc(t_token *tk, int i);
void				close_hrdc(t_shell *mini, int cur, int sw);
int					nb_hrdc(t_shell *mini);
int					is_hrdc(t_token *tk);

/* redir.c */
void				redir(t_shell *mini, t_token *tk, int i);

/* redir_u.c */
void				redir_close(t_shell *mini, t_token *tk);
void				args_redir(t_shell *mini, t_token *tk);
int					is_redir(t_token *tk, int mode);

/* error.c */
void				err_manager(t_shell *mini, t_token *tk, int err);
void				fds_err(t_shell *mini, char *fname);

#endif