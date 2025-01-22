/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:16:33 by jmathieu          #+#    #+#             */
/*   Updated: 2023/09/22 12:47:16 by jlecorne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	alpha_num_underscore(char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		if (s[0] == '=')
			return (0);
		else if (s[0] == '_' && s[1] == '=')
			return (2);
		else if (!ft_isalpha(s[0]))
			return (0);
		else if (ft_isalnum(s[i]) || s[i] == '_')
			i++;
		else if (s[i] == '=')
			break ;
		else
			return (0);
	}
	if (s && (s[i] == '=' || !s[i]))
		return (1);
	return (0);
}

static void	not_a_variable(t_shell *mini, t_token *list)
{
	mini->rtn = 1;
	ft_putstr_fd("minishell: export: `", STDERR_FILENO);
	ft_putstr_fd(list->s, STDERR_FILENO);
	ft_putstr_fd("': Not a valid identifier\n", STDERR_FILENO);
}

void	b_export_args(t_shell *mini, t_token *list, int nb_args)
{
	int		lines;
	char	*var;

	while (nb_args > 0)
	{
		lines = tab_lines(mini->env);
		var = var_name(mini, list->s);
		if (!alpha_num_underscore(list->s))
			not_a_variable(mini, list);
		else if (alpha_num_underscore(list->s) == 2)
			continue ;
		else if (existing_var(mini, var) == -1)
			mini->env = add_var_env(mini, lines + 1, list);
		else
			sub_var_env(mini, lines, list);
		list = list->next;
		nb_args--;
		free_str(var);
	}
}

void	b_export(t_shell *mini, t_token *list)
{
	int	nb_args;

	if (!list->next || (!check_nb_args(list, 1) && !check_nb_args(list, 2))
		|| (list->next && list->next->s == NULL))
		print_listed_env(mini);
	else
	{
		nb_args = check_nb_args(list, 1) + check_nb_args(list, 2);
		list = list->next;
		b_export_args(mini, list, nb_args);
	}
}
