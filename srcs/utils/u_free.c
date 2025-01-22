/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_free.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:16:33 by jmathieu          #+#    #+#             */
/*   Updated: 2023/09/21 13:59:46 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_str(char *tmp)
{
	if (tmp)
	{
		free(tmp);
		tmp = NULL;
	}
}

void	free_tab(char **tab)
{
	int	i;

	i = -1;
	if (tab)
	{
		while (tab[++i])
			free_str(tab[i]);
		free(tab);
	}
}

void	free_env(t_shell *mini)
{
	int	i;

	i = -1;
	while (mini->env[++i])
	{
		free(mini->env[i]);
		mini->env[i] = NULL;
	}
	free(mini->env);
}

void	free2(char *one, char *two)
{
	free_str(one);
	free_str(two);
}
