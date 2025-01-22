/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_sig.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:03:28 by jmathieu          #+#    #+#             */
/*   Updated: 2023/09/20 19:37:36 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	define_last(t_shell *mini)
{
	if (g_sig == 131)
		mini->rtn = 131;
	else if (g_sig == 130)
		mini->rtn = 130;
	g_sig = 0;
}

static void	sigint_std(void)
{
	rl_redisplay();
	rl_replace_line("", 0);
	ft_putstr_fd("\n", STDERR_FILENO);
	rl_on_new_line();
	rl_redisplay();
}

static void	sigint(int sig)
{
	(void)sig;
	if (g_sig == 0)
		sigint_std();
	else if (g_sig == 1)
		sigint_forked();
}

static void	sigquit(int sig)
{
	(void)sig;
	if (g_sig == 1)
		sigquit_forked();
}

void	define_signals(void)
{
	signal(SIGINT, sigint);
	signal(SIGQUIT, sigquit);
}
