/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd_exce.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 16:31:39 by jmathieu          #+#    #+#             */
/*   Updated: 2023/09/21 16:11:25 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	modify_pwd_and_tmp(t_shell *mini, char *tmp)
{
	int	i;

	i = existing_var(mini, "PWD");
	if (i != -1)
	{
		free(mini->env[i]);
		mini->env[i] = NULL;
		mini->env[i] = ft_strjoin("PWD=", tmp);
	}
	mini->rtn = 0;
}

void	modify_pwd(t_shell *mini, t_token *list)
{
	int	i;

	i = existing_var(mini, "PWD");
	if (i != -1)
	{
		free(mini->env[i]);
		mini->env[i] = NULL;
		mini->env[i] = ft_strjoin("PWD=", list->s);
	}
	mini->rtn = 0;
}

char	*modify_oldpwd(t_shell *mini, char *tmp_pwd)
{
	int		i;
	char	*tmp;

	tmp = NULL;
	i = existing_var(mini, "PWD");
	if (i != -1)
		tmp = return_var_content(mini, mini->env[i]);
	i = existing_var(mini, "OLDPWD");
	free(mini->env[i]);
	mini->env[i] = NULL;
	mini->env[i] = ft_strjoin("OLDPWD=", tmp_pwd);
	return (tmp);
}

static void	modify_env(t_shell *mini, t_token *list, char *cur_dir)
{
	int		i;
	char	*tmp;

	tmp = NULL;
	i = existing_var(mini, "OLDPWD");
	if (i != -1)
	{
		tmp = modify_oldpwd(mini, cur_dir);
		if (list->s[0] == '-' && list->s[1] == 0)
		{
			modify_pwd_and_tmp(mini, tmp);
			free_str(tmp);
			return ;
		}
		free_str(tmp);
	}
	free(list->s);
	list->s = NULL;
	list->s = getcwd(NULL, 0);
	if (!list->s)
		ft_exit_plus(mini, "No directory\n", 1);
	modify_pwd(mini, list);
}

void	check_var_status(t_shell *mini, t_token *list, char *tmp_path,
	char *cur_dir)
{
	if ((existing_var(mini, "PWD")) == -1)
	{
		if (!valid_path(mini, tmp_path))
		{
			free_str(cur_dir);
			return ;
		}
	}
	else
	{
		if (!valid_path(mini, tmp_path))
		{
			free_str(cur_dir);
			return ;
		}
	}
	modify_env(mini, list, cur_dir);
	if (cur_dir)
		free_str(cur_dir);
}
