/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_sig_piped.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:03:34 by jmathieu          #+#    #+#             */
/*   Updated: 2023/09/20 19:31:03 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	sigint_piped(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", STDERR_FILENO);
	g_sig = 130;
}

void	sigquit_piped(int sig)
{
	(void)sig;
	ft_putstr_fd("Quit: 3\n", STDOUT_FILENO);
	g_sig = 131;
}

void	piped_sig(void)
{
	signal(SIGINT, sigint_piped);
	signal(SIGQUIT, sigquit_piped);
}
