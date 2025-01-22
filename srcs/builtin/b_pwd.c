/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_pwd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:15:31 by jmathieu          #+#    #+#             */
/*   Updated: 2023/09/20 18:27:46 by jlecorne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	b_pwd(t_shell *mini)
{
	char	*pathnewline;
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
		ft_exit_plus(mini, "Fail to access directory\n", 1);
	pathnewline = ft_strjoin(path, "\n");
	ft_putstr_fd(pathnewline, STDOUT_FILENO);
	free_str(path);
	free_str(pathnewline);
	mini->rtn = 0;
	return ;
}
