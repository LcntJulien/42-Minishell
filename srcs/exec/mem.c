/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 14:49:24 by jlecorne          #+#    #+#             */
/*   Updated: 2023/09/25 15:45:48 by jlecorne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	mini_free(t_shell *mini)
{
	if (g_sig != 0)
		define_last(mini);
	free_htab(mini);
	free_pipe(mini);
	free_paths(mini);
	free_args(mini);
	free_token(mini);
	if (mini->pid)
		free(mini->pid);
	mini->pid = NULL;
	if (mini->cmd)
		free(mini->cmd);
	mini->cmd = NULL;
	if (mini->line)
		free(mini->line);
	mini->line = NULL;
	mini->ncmd = 0;
	define_signals();
}

void	pipe_alloc(t_shell *mini)
{
	int	i;

	i = -1;
	mini->tab = malloc(sizeof(int *) * mini->ncmd);
	if (!mini->tab)
		err_manager(mini, NULL, 3);
	while (++i < mini->ncmd)
	{
		mini->tab[i] = malloc(sizeof(int) * 2);
		if (!mini->tab[i])
			err_manager(mini, NULL, 3);
	}
	mini->pid = malloc(sizeof(pid_t) * mini->ncmd);
	if (!mini->pid)
		err_manager(mini, NULL, 3);
	i = -1;
	while (++i < mini->ncmd)
		if (pipe(mini->tab[i]) < 0)
			err_manager(mini, NULL, 1);
}

void	close_redir(t_shell *mini, t_token *tk)
{
	if (is_redir(tk, 1))
		close(mini->in);
	if (is_redir(tk, 2))
		close(mini->out);
}

void	close_output(t_token *tk, t_token *cur)
{
	t_token	*cp;
	int		fd;

	cp = tk;
	fd = 0;
	while (cp->prev && cp->prev->type != PIPE)
		cp = cp->prev;
	while (cp && cp->type != PIPE)
	{
		if (cp->next && (cp->type == OUTPUT || cp->type == APPEND)
			&& (ft_strncmp(cp->next->s, cur->s, ft_strlen(cur->s)) != 0
				|| ft_strlen(cp->next->s) != ft_strlen(cur->s)))
		{
			fd = open(cp->next->s, O_CREAT | O_RDWR | O_TRUNC, 0644);
			close(fd);
		}
		cp = cp->next;
	}
}

void	close_pipes(t_shell *mini, t_token *tk, int i, int sw)
{
	int	j;

	j = -1;
	if (sw)
	{
		while (++j < mini->ncmd)
		{
			if (j != i || i == 0 || (j == i && is_redir(tk, 1)))
				close(mini->tab[j][0]);
			if (j != (i + 1))
				close(mini->tab[j][1]);
		}
	}
	else
	{
		while (++j < mini->ncmd)
		{
			close(mini->tab[j][0]);
			close(mini->tab[j][1]);
		}
	}
}
