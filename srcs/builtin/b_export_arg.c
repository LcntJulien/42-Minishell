/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:16:33 by jmathieu          #+#    #+#             */
/*   Updated: 2023/09/22 14:28:11 by jlecorne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	sub_var_env_next(t_shell *mini, int i, t_token *sub, char *s1)
{
	free_str(mini->env[i]);
	mini->env[i] = ft_strdup(sub->s);
	if (!mini->env[i])
	{
		free_str(s1);
		ft_exit_plus(mini, "Fail to modify the environnement\n", 1);
	}
}

void	sub_var_env(t_shell *mini, int lines, t_token *sub)
{
	int		i;
	char	*s1;
	char	*s2;

	i = 0;
	s1 = var_name(mini, sub->s);
	while (i < lines)
	{
		s2 = var_name(mini, mini->env[i]);
		if (!ft_strncmp(s1, s2, ft_strlen(s1)))
		{
			if ((is_there_an_equal(mini->env[i])
					&& is_there_an_equal(sub->s))
				|| (!is_there_an_equal(mini->env[i])
					&& is_there_an_equal(sub->s)))
				sub_var_env_next(mini, i, sub, s1);
		}
		if (s2)
			free_str(s2);
		i++;
	}
	free_str(s1);
}

char	**add_var_env(t_shell *mini, int lines, t_token *new)
{
	int		i;
	char	**tmp;

	i = 0;
	tmp = ft_calloc((lines + 1), sizeof(char *));
	if (!tmp)
		ft_exit_plus(mini, "Fail to allocate memory\n", 1);
	while (mini->env[i])
	{
		tmp[i] = ft_strdup(mini->env[i]);
		i++;
	}
	tmp[i] = ft_strdup(new->s);
	free_env(mini);
	if (!tmp[i])
		ft_exit_plus(mini, "Fail to register a variable\n", 1);
	return (tmp);
}
