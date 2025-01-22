/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 16:31:16 by jmathieu          #+#    #+#             */
/*   Updated: 2023/09/25 13:08:04 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*check_str_cd(t_shell *mini, t_token *list)
{
	char	*tmp_path;

	if (ft_strncmp(list->s, "-", 1) == 0 && list->s[1] == 0)
		tmp_path = folder1(mini);
	else if (ft_strncmp(list->s, "~", 1) == 0)
		tmp_path = folder2(mini, list);
	else
		tmp_path = ft_strdup(list->s);
	return (tmp_path);
}

void	next_cd_step(t_shell *mini, t_token *list, char *cur_dir)
{
	char	*tmp_path;

	if (ft_strncmp(list->s, "..", 2) != 0)
	{
		tmp_path = check_str_cd(mini, list);
		if (ft_strncmp(tmp_path, "HOME", 4) == 0
			|| ft_strncmp(tmp_path, "OLDPWD", 6) == 0)
		{
			mini->rtn = 1;
			ft_putstr_fd("minishell: cd: ", STDOUT_FILENO);
			ft_putstr_fd(tmp_path, STDOUT_FILENO);
			ft_putstr_fd(" not set\n", STDOUT_FILENO);
			free_str(tmp_path);
			free_str(cur_dir);
			return ;
		}
		check_var_status(mini, list, tmp_path, cur_dir);
		free_str(tmp_path);
	}
	else
		check_var_status(mini, list, list->s, cur_dir);
}

static int	args_before_cd(t_shell *mini, t_token *list)
{
	if (existing_var(mini, "HOME=") == -1)
	{
		mini->rtn = 1;
		ft_putstr_fd("minishell: cd: HOME not set\n", STDOUT_FILENO);
		return (0);
	}
	else
	{
		free(list->s);
		list->s = NULL;
		list->s = return_var_content(mini, "HOME=");
		return (1);
	}
}

void	b_cd(t_shell *mini, t_token *list)
{
	char	*cur_dir;

	cur_dir = getcwd(NULL, 0);
	if (cur_dir == 0)
	{
		free_str(cur_dir);
		ft_exit_plus(mini, "Not a directory\n", 1);
	}
	else if (!list->next || (list->next && list->next->type >= 6))
	{
		if (!args_before_cd(mini, list))
		{
			free_str(cur_dir);
			return ;
		}
	}
	else
		list = list->next;
	next_cd_step(mini, list, cur_dir);
}
