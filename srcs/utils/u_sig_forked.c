/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_sig_forked.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:03:34 by jmathieu          #+#    #+#             */
/*   Updated: 2023/09/20 19:37:31 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	sigint_forked(void)
{
	ft_putstr_fd("\n", STDERR_FILENO);
	rl_redisplay();
	g_sig = 130;
}

void	sigquit_forked(void)
{
	ft_putstr_fd("Quit: 3\n", STDOUT_FILENO);
	rl_redisplay();
	g_sig = 131;
}

void	signal_forked(t_token *tk)
{
	(void)tk;
	g_sig = 1;
	if (is_hrdc(tk))
		replace_sig();
}
