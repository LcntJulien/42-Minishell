/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_process.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 16:53:11 by jmathieu          #+#    #+#             */
/*   Updated: 2023/09/21 14:00:27 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	b_process(t_shell *mini, t_token *tk)
{
	g_sig = 0;
	if (tk && !ft_strncmp(tk->s, "echo", 4))
		b_echo(mini, tk);
	else if (tk && !ft_strncmp(tk->s, "cd", 2))
		b_cd(mini, tk);
	else if (tk && !ft_strncmp(tk->s, "pwd", 3))
		b_pwd(mini);
	else if (tk && !ft_strncmp(tk->s, "export", 6))
		b_export(mini, tk);
	else if (tk && !ft_strncmp(tk->s, "unset", 5))
		b_unset(mini, tk);
	else if (tk && !ft_strncmp(tk->s, "env", 3))
		b_env(mini, tk);
	else if (tk && !ft_strncmp(tk->s, "exit", 4))
		b_exit(mini, tk);
	return ;
}
