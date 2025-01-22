/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_unset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:16:40 by jmathieu          #+#    #+#             */
/*   Updated: 2023/09/22 12:46:37 by jlecorne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	**delete_var(t_shell *mini, int i)
{
	int		j;
	int		len;
	char	**new_env;

	j = -1;
	len = tab_lines(mini->env) - 1;
	new_env = ft_calloc(sizeof(char *), (len + 1));
	if (!new_env)
		ft_exit_plus(mini, "Fail to allocate memory\n", 1);
	len = -1;
	while (mini->env[++len])
	{
		if (len != i)
			new_env[++j] = ft_strdup(mini->env[len]);
	}
	free_env(mini);
	return (new_env);
}

static void	b_unset_args(t_shell *mini, t_token *list, int nb_args)
{
	int		i;
	char	*str;

	while (nb_args > 0)
	{
		i = existing_var(mini, list->s);
		if (i != -1)
		{
			str = return_var_name(mini, list->s);
			if (ft_strncmp("_", str, ft_strlen(str)))
				mini->env = delete_var(mini, i);
			free(str);
		}
		mini->rtn = 0;
		list = list->next;
		nb_args--;
	}
	return ;
}

static void	unset_error(t_shell *mini, t_token *list)
{
	mini->rtn = 1;
	ft_putstr_fd("minishell: unset: `", STDERR_FILENO);
	ft_putstr_fd(list->s, STDERR_FILENO);
	ft_putstr_fd("': Not a valid identifier\n", STDERR_FILENO);
}

void	b_unset(t_shell *mini, t_token *list)
{
	int		nb_args;
	t_token	*tmp;

	nb_args = 0;
	if (!list->next)
		return ;
	else
	{
		tmp = mini->token->next;
		if (tmp && tmp->type == 2 && tmp->s != NULL)
		{
			unset_error(mini, tmp);
			return ;
		}
		while (tmp && tmp->type == 1)
		{
			nb_args++;
			tmp = tmp->next;
		}
		if (nb_args == 0)
			return ;
		list = mini->token->next;
		b_unset_args(mini, list, nb_args);
	}
}
