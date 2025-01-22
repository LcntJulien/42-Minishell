/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 16:11:51 by jmathieu          #+#    #+#             */
/*   Updated: 2023/09/21 13:15:11 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_exit_plus(t_shell *mini, char *err, int rtn)
{
	if (mini->home)
		free_str(mini->home);
	if (mini->env)
		free_env(mini);
	if (mini->token)
		free_token(mini);
	if (mini->args)
		free_tab(mini->args);
	if (mini->paths)
		free_tab(mini->paths);
	if (rtn != 126 && rtn != 127)
		ft_putstr_fd(err, STDERR_FILENO);
	exit(rtn);
}

void	ft_exit_all(t_shell *mini, int histo, int rtn)
{
	close(histo);
	mini_free(mini);
	if (mini->env)
		free_env(mini);
	exit(rtn);
}
