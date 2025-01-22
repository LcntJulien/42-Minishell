/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 20:57:29 by jlecorne          #+#    #+#             */
/*   Updated: 2023/09/21 14:06:23 by jlecorne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_htab(t_shell *mini)
{
	int	i;

	i = 0;
	if (mini->htab)
	{
		while (i < nb_hrdc(mini))
			free(mini->htab[i++]);
		free(mini->htab);
		mini->htab = NULL;
	}
}

void	free_token(t_shell *mini)
{
	t_token	*cpy;
	t_token	*tmp;

	cpy = mini->token;
	tmp = NULL;
	while (cpy)
	{
		tmp = cpy->next;
		if (cpy->s)
		{
			free(cpy->s);
			cpy->s = NULL;
		}
		free(cpy);
		cpy = tmp;
	}
	mini->token = NULL;
}

void	free_args(t_shell *mini)
{
	int	i;

	i = 0;
	if (mini->args)
	{
		while (mini->args[i])
			free(mini->args[i++]);
		free(mini->args);
		mini->args = NULL;
	}
}

void	free_pipe(t_shell *mini)
{
	int	i;

	i = 0;
	if (mini->tab)
	{
		while (i < mini->ncmd)
			free(mini->tab[i++]);
		free(mini->tab);
		mini->tab = NULL;
	}
}

void	free_paths(t_shell *mini)
{
	int	i;

	i = 0;
	if (mini->paths)
	{
		while (mini->paths[i])
			free(mini->paths[i++]);
		free(mini->paths);
		mini->paths = NULL;
	}
}
