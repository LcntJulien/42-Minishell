/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_env_excepts.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 16:25:39 by jmathieu          #+#    #+#             */
/*   Updated: 2023/08/31 15:00:00 by jlecorne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_last(t_shell *mini, char **env, int i)
{
	char	*str;
	char	*pwd;

	pwd = NULL;
	str = NULL;
	if (!ft_strncmp(env[i], "_=", 2))
	{
		pwd = getcwd(NULL, 0);
		if (!pwd)
			ft_exit_plus(mini, "Fail to access to the folder\n", 1);
		str = ft_strjoin("_=", pwd);
		free_str(pwd);
		mini->env[i] = ft_strjoin(str, "/minishell");
		free_str(str);
		return (1);
	}
	return (0);
}

int	check_shlvl(t_shell *mini, char **env, int i)
{
	int		shlvl;
	char	*str;

	shlvl = 0;
	str = NULL;
	if (!ft_strncmp(env[i], "SHLVL=", 5))
	{
		shlvl = get_shlvl(env[i]) + 1;
		if (shlvl == -1 || shlvl == 0)
			ft_exit_plus(mini, "Fail to initiate bash level\n", 1);
		str = ft_itoa(shlvl);
		mini->env[i] = ft_strjoin("SHLVL=", str);
		free_str(str);
		return (1);
	}
	return (0);
}

int	check_oldpwd(t_shell *mini, char **env, int i)
{
	if (!ft_strncmp(env[i], "OLDPWD=", 7))
	{
		mini->env[i] = ft_substr(env[i], 0, 6);
		return (1);
	}
	return (0);
}
