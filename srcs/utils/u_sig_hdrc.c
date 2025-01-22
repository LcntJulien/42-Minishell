/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_sig_hdrc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:03:34 by jmathieu          #+#    #+#             */
/*   Updated: 2023/09/20 18:11:03 by jlecorne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	sigint_hrdc(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", STDERR_FILENO);
	rl_redisplay();
	exit(1);
}

static void	sigquit_hrdc(int sig)
{
	(void)sig;
}

void	signals_hrdc(void)
{
	signal(SIGINT, sigint_hrdc);
	signal(SIGQUIT, sigquit_hrdc);
}

void	replace_sig(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}
