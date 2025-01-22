/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:16:20 by jmathieu          #+#    #+#             */
/*   Updated: 2023/09/20 20:32:32 by jlecorne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	args_to_print(t_token *list, int nb_opt)
{
	int		nb_args;

	nb_args = 0;
	while (nb_opt > 0)
	{
		nb_opt--;
		list = list->next;
	}
	while (list && ((list->type >= 0 && list->type <= 5)))
	{
		nb_args++;
		list = list->next;
	}
	return (nb_args);
}

static int	valid_option(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (str[i] != '-')
		return (0);
	else
	{
		i++;
		while (str[i] == 'n')
			i++;
		if (str[i] && str[i] != ' ')
			return (0);
		else
			return (1);
	}
}

static int	nb_option(t_token *list)
{
	int		nb_opt;

	nb_opt = 0;
	while (list && list->type == 3)
	{
		if (!valid_option(list->s))
			break ;
		nb_opt++;
		list = list->next;
	}
	return (nb_opt);
}

static void	print_echo(t_token *list, int nb_args, int nb_opt)
{
	int	nextline;

	nextline = nb_opt;
	while (nb_opt > 0)
	{
		list = list->next;
		nb_opt--;
	}
	while (nb_args > 0)
	{
		ft_putstr_fd(list->s, STDOUT_FILENO);
		nb_args--;
		if (list->next && nb_args > 0)
			ft_putstr_fd(" ", STDOUT_FILENO);
		else
			break ;
		list = list->next;
	}
	if (nextline == 0)
		ft_putstr_fd("\n", STDOUT_FILENO);
}

void	b_echo(t_shell *mini, t_token *list)
{
	int		nb_args;
	int		nb_opt;

	if (!list->next)
	{
		mini->rtn = 0;
		return ;
	}
	else
	{
		list = list->next;
		nb_opt = nb_option(list);
		if (!list)
			return ;
		if (!check_opt(list, nb_opt))
			return ;
		nb_args = args_to_print(list, nb_opt);
		print_echo(list, nb_args, nb_opt);
		mini->rtn = 0;
	}
}
