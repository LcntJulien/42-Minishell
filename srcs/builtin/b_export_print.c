/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export_print.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:16:33 by jmathieu          #+#    #+#             */
/*   Updated: 2023/09/21 12:53:23 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	print_export_to_fd(char *name, char *s1, char *content, int i)
{
	char	*s2;

	s2 = NULL;
	if (i == 0)
	{
		s1 = ft_strjoin("declare -x ", name);
		s2 = ft_strjoin(s1, "\n");
		ft_putstr_fd(s2, STDOUT_FILENO);
	}
	else
	{
		s1 = ft_strjoin("declare -x ", name);
		s2 = ft_strjoin(s1, "=\"");
		free_str(s1);
		s1 = ft_strjoin(s2, content);
		free_str(s2);
		s2 = ft_strjoin(s1, "\"\n");
		ft_putstr_fd(s2, STDOUT_FILENO);
	}
	free_str(s1);
	free_str(s2);
}

static void	print_export(t_shell *mini, char **exp)
{
	int		i;
	char	*s;
	char	*name;
	char	*content;

	i = 0;
	s = NULL;
	while (exp[i])
	{
		if (ft_strncmp(exp[i], "_=", 2))
		{
			name = var_name(mini, exp[i]);
			content = var_content(mini, exp[i]);
			if (!is_there_an_equal(exp[i]))
				print_export_to_fd(name, s, content, 0);
			else
				print_export_to_fd(name, s, content, 1);
			free_str(name);
			free_str(content);
		}
		i++;
	}
}

static void	sort_in_tab(char **exp, int lines)
{
	int		i;
	int		j;
	int		len;
	char	*tmp;

	j = 1;
	while (j < lines)
	{
		i = 0;
		while (i < j)
		{
			len = max_len(ft_strlen(exp[i]), ft_strlen(exp[j]));
			if (ft_strncmp(exp[i], exp[j], len) > 0)
			{
				tmp = exp[i];
				exp[i] = exp[j];
				exp[j] = tmp;
			}
			else
				i++;
		}
		j++;
	}
}

static void	copy_tab(t_shell *mini, char **exp)
{
	int	i;

	i = 0;
	while (mini->env[i])
	{
		exp[i] = strdup(mini->env[i]);
		i++;
	}
}

void	print_listed_env(t_shell *mini)
{
	int		lines;
	int		i;
	char	**exp;

	i = -1;
	lines = tab_lines(mini->env);
	exp = ft_calloc((lines + 1), sizeof(char *));
	if (!exp)
		ft_exit_plus(mini, "Not enough memory\n", 1);
	copy_tab(mini, exp);
	sort_in_tab(exp, lines);
	print_export(mini, exp);
	while (exp[++i])
		free_str(exp[i]);
	free(exp);
	mini->rtn = 0;
}
