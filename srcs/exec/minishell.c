/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 15:28:35 by jlecorne          #+#    #+#             */
/*   Updated: 2023/09/25 15:24:45 by jlecorne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	close_child(t_shell *mini, t_token *tk, int i)
{
	if (i == 0 && !is_redir(tk, 2))
		close(mini->tab[i + 1][1]);
	else if (i == mini->ncmd - 1 && !is_redir(tk, 1))
		close(mini->tab[i][0]);
	else if (i != 0 && i != mini->ncmd - 1)
	{
		if (!is_redir(tk, 1))
			close(mini->tab[i][0]);
		if (!is_redir(tk, 2))
			close(mini->tab[i + 1][1]);
	}
	if (is_redir(tk, 2))
		close(mini->out);
	if (is_redir(tk, 1) && !is_hrdc(tk))
		close(mini->in);
}

void	exec(t_shell *mini, t_token *tk, int i)
{
	g_sig = 1;
	if (mini->ncmd == 1 && is_redir(tk, 0))
		redir(mini, tk, i);
	if (tk && tk->type == BUILTIN)
	{
		b_process(mini, tk);
		dup2(mini->o_in, STDIN_FILENO);
		dup2(mini->o_out, STDOUT_FILENO);
		if (mini->ncmd > 1)
		{
			free_env(mini);
			exit(0);
		}
	}
	else if (tk)
	{
		get_args(mini, tk);
		if (!mini->args)
			exit(0);
		mini->cmd = get_cmd(mini);
		if (!mini->cmd)
			err_manager(mini, tk, 0);
		execve(mini->cmd, mini->args, mini->env);
		exit(EXIT_FAILURE);
	}
}

void	child(t_shell *mini, t_token *tk, int i)
{
	if (is_redir(tk, 0))
		redir(mini, tk, i);
	if (i == 0 && !is_redir(tk, 2))
		dup2(mini->tab[i + 1][1], STDOUT_FILENO);
	else if (i == mini->ncmd - 1 && !is_redir(tk, 1))
		dup2(mini->tab[i][0], STDIN_FILENO);
	else if (i != 0 && i != mini->ncmd - 1)
	{
		if (!is_redir(tk, 1))
			dup2(mini->tab[i][0], STDIN_FILENO);
		if (!is_redir(tk, 2))
			dup2(mini->tab[i + 1][1], STDOUT_FILENO);
	}
	close_redir(mini, tk);
	close_pipes(mini, tk, i, 1);
	close_hrdc(mini, i, 1);
	exec(mini, tk, i);
}

void	minipipe(t_shell *mini, t_token *tk)
{
	int	i;

	i = -1;
	pipe_alloc(mini);
	hrdc_manager(mini);
	while (++i < mini->ncmd && g_sig <= 1)
	{
		piped_sig();
		mini->pid[i] = fork();
		if (mini->pid[i] == -1)
			err_manager(mini, NULL, 2);
		else if (mini->pid[i] == 0)
			child(mini, tk, i);
		tk = next_cmd(tk);
	}
	i = -1;
	close_pipes(mini, tk, i, 0);
	close_hrdc(mini, i, 0);
	close_redir(mini, tk);
	while (++i < mini->ncmd)
	{
		waitpid(mini->pid[i], &mini->rtn, 0);
		mini->rtn = WEXITSTATUS(mini->rtn);
	}
}

void	minishell(t_shell *mini)
{
	t_token	*tk;
	pid_t	pid;

	tk = mini->token;
	tk = find_cmd(tk);
	if (mini->ncmd > 1)
		minipipe(mini, tk);
	else if (mini->ncmd == 1)
	{
		hrdc_manager(mini);
		if (mini->token && tk->type == BUILTIN)
			exec(mini, tk, 0);
		else if (mini->token)
		{
			signal_forked(tk);
			pid = fork();
			if (pid < 0)
				err_manager(mini, tk, 2);
			else if (pid == 0)
				exec(mini, tk, 0);
			close_hrdc(mini, 0, 0);
			waitpid(pid, &mini->rtn, 0);
			mini->rtn = WEXITSTATUS(mini->rtn);
		}
	}
}
