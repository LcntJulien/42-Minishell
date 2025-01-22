/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 14:39:05 by jlecorne          #+#    #+#             */
/*   Updated: 2023/09/25 16:48:28 by jlecorne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	fds_err(t_shell	*mini, char	*fname)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(fname, 2);
	ft_putendl_fd(": no such file or directory", 2);
	mini->rtn = 1;
	exit(1);
}

void	err_manager(t_shell *mini, t_token *tk, int err)
{
	ft_putstr_fd("minishell: ", 2);
	if (!err)
	{
		if (tk && tk->s)
		{
			convert_var(mini, tk);
			ft_putstr_fd(tk->s, 2);
		}
		ft_putendl_fd(": command not found", 2);
		mini->rtn = 127;
		exit(127);
	}
	else if (err == 1)
		ft_putendl_fd("error creating pipe", 2);
	else if (err == 2)
		ft_putendl_fd("error forking process id", 2);
	else if (err == 3)
		ft_putendl_fd("failed to allocate space", 2);
	mini->rtn = EXIT_FAILURE;
	ft_exit_all(mini, 0, EXIT_FAILURE);
}
