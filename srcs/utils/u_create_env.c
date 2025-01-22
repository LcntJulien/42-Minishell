/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_create_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:16:54 by jmathieu          #+#    #+#             */
/*   Updated: 2023/08/29 12:53:27 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_more_alloc(char **env, int *f_old, int *f_sh)
{
	int	i;
	int	flag;

	i = -1;
	flag = 2;
	while (env[++i])
	{
		if (!ft_strncmp(env[i], "OLDPWD", 6))
			(*f_old)++;
		if (!ft_strncmp(env[i], "SHLVL", 5))
			(*f_sh)++;
	}
	flag = flag - (*f_old + *f_sh);
	return (flag);
}

int	get_shlvl(char *str)
{
	int		i;
	int		start;
	int		end;	
	char	*shlvl;

	i = 0;
	start = 0;
	while (str[start] && str[start] != '=')
		start++;
	end = ft_strlen(str);
	shlvl = ft_calloc(sizeof(char), (end - start));
	if (!shlvl)
		return (-1);
	while (str[++start])
		shlvl[i++] = str[start];
	i = ft_atoi(shlvl);
	free_str(shlvl);
	return (i);
}

static int	env_exceptions(t_shell *mini, char **env, int i)
{
	if (check_oldpwd(mini, env, i))
		return (1);
	else if (check_shlvl(mini, env, i))
		return (1);
	else if (check_last(mini, env, i))
		return (1);
	else
		return (0);
}

static void	copy_env(t_shell *mini, char **env, int f_old, int f_sh)
{
	int	i;

	i = -1;
	if (!env)
	{
		mini->env[0] = NULL;
		return ;
	}
	while (env[++i])
	{
		if (!env_exceptions(mini, env, i))
		{
			mini->env[i] = ft_strdup(env[i]);
			if (!mini->env[i])
				ft_exit_plus(mini, "Fail to initiate environnement\n", 1);
		}
	}
	if (f_sh == 0)
		mini->env[i++] = ft_strdup("SHLVL=1");
	if (f_old == 0)
		mini->env[i] = ft_strdup("OLDPWD");
}

void	alloc_env(t_shell *mini, char **env)
{
	int		flag;
	int		f_old;
	int		f_sh;
	int		lines;

	if (!env)
	{
		ft_putstr_fd("Fail to load previous environnement\n", 2);
		exit(1);
	}
	f_old = 0;
	f_sh = 0;
	flag = ft_more_alloc(env, &f_old, &f_sh);
	lines = tab_lines(env);
	mini->env = ft_calloc((lines + flag + 1), sizeof(char *));
	if (!mini->env)
	{
		ft_putstr_fd("Fail to allocate memory !\n", 2);
		exit(1);
	}
	copy_env(mini, env, f_old, f_sh);
}
