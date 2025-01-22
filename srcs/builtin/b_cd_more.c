/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd_more.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 11:38:46 by jmathieu          #+#    #+#             */
/*   Updated: 2023/09/21 16:06:25 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*folder2(t_shell *mini, t_token *list)
{
	char	*str1;
	char	*str2;

	if (list->s[1] && list->s[1] == '/')
	{
		str1 = ft_strjoin(mini->home, "/");
		str2 = ft_strjoin(str1, list->s);
		free_str(str1);
		return (str2);
	}
	else if (!list->s[1])
		return (ft_strdup(mini->home));
	else
		return (ft_strjoin(mini->home, list->s));
}

char	*folder1(t_shell *mini)
{
	int	i;

	i = existing_var(mini, "OLDPWD");
	if (i != -1 && ft_strncmp("OLDPWD=", mini->env[i], 7) == 0)
		return (var_content(mini, mini->env[existing_var(mini,
						"OLDPWD")]));
	else
		return (ft_strdup("OLDPWD"));
}

int	valid_path(t_shell *mini, char *tmp_path)
{
	char	*str;

	str = NULL;
	if (chdir(tmp_path) == -1)
	{
		mini->rtn = 1;
		str = ft_strjoin("minishell: cd: ", tmp_path);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		free_str(str);
		return (0);
	}
	else
		return (1);
}

static void	print_error(t_shell *mini, char *tmp, int i)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(mini->args[0], STDERR_FILENO);
	ft_putstr_fd(": Not a directory\n", STDERR_FILENO);
	free_str(tmp);
	exit(i);
}

void	test_access(t_shell *mini)
{
	char		*path;
	char		*tmp;
	char		*tmp2;
	struct stat	info;

	tmp = getcwd(NULL, 0);
	if (tmp)
	{
		path = ft_strjoin(tmp, "/");
		free_str(tmp);
		tmp = ft_strdup(path);
		free_str(path);
		tmp2 = ft_strjoin(tmp, mini->args[0]);
		free_str(tmp);
		path = ft_substr(tmp2, 0, ft_strlen(tmp2) - 1);
		free_str(tmp2);
		if (stat(path, &info) == 0)
		{
			if (S_ISREG(info.st_mode))
				print_error(mini, path, 126);
		}
		else
			free_str(path);
	}
}
