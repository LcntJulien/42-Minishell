/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_var.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 13:22:34 by jmathieu          #+#    #+#             */
/*   Updated: 2023/08/31 14:55:45 by jlecorne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*check_condition(t_shell *mini, t_token *tmp)
{
	char	*s;
	char	*str;

	s = NULL;
	str = NULL;
	if (tmp->type == 0)
		s = ft_strjoin("/bin/", tmp->s);
	else if (tmp->type == 2)
	{
		str = var_name(mini, tmp->s);
		s = return_var_content(mini, str);
		free_str(str);
	}
	else if (tmp->type == 5)
		s = return_var_name(mini, tmp->s);
	else
		s = ft_strdup(tmp->s);
	if (!s)
		ft_exit_plus(mini, "Fail to allocate memory\n", 1);
	return (s);
}

static void	just_a_return(t_shell *mini, int i)
{
	while (mini->env[++i])
	{
		if (!ft_strncmp("_=", mini->env[i], 2))
		{
			free_str(mini->env[i]);
			mini->env[i] = ft_strdup("_=");
		}
	}
}

static char	*define_last_arg_to_write(t_shell *mini, t_token *tmp)
{
	char	*s;

	s = NULL;
	while (tmp)
	{
		if (tmp->type < 6)
		{
			if (tmp->next && tmp->next->type < 6)
				tmp = tmp->next;
			else
			{
				s = check_condition(mini, tmp);
				break ;
			}
		}
		else
			break ;
	}
	return (s);
}

void	sub_var_last_cmd(t_shell *mini)
{
	int		i;
	char	*s;
	t_token	*tmp;

	i = -1;
	tmp = mini->token;
	s = define_last_arg_to_write(mini, tmp);
	if (s)
	{
		while (mini->env[++i])
		{
			if (!ft_strncmp("_=", mini->env[i], 2))
			{
				free_str(mini->env[i]);
				mini->env[i] = ft_strjoin("_=", s);
				free_str(s);
			}
		}
	}
	else
		just_a_return(mini, i);
}
