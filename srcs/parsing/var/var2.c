/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 13:56:10 by jmathieu          #+#    #+#             */
/*   Updated: 2023/09/20 23:08:20 by jlecorne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	*other_variable(t_shell *mini, t_token *tk, int i)
{
	char	*new_var;

	new_var = NULL;
	if (tk->s[i] == '$')
		new_var = ft_itoa(getpid());
	else if (tk->s[i])
		new_var = ft_itoa(mini->rtn);
	return (new_var);
}

char	*get_other_var(char *vname)
{
	char	*tmp;
	char	*nvar;
	int		i;

	tmp = ft_calloc(sizeof(char), ft_strlen(vname) + 2);
	nvar = NULL;
	i = -1;
	while (vname[++i])
		tmp[i] = vname[i];
	tmp[i] = '=';
	i = -1;
	free(tmp);
	return (nvar);
}

char	*rewrite2(char *s, char *iter, int idx)
{
	char	*ns;
	int		i;
	int		j;

	ns = ft_calloc(sizeof(char), ((ft_strlen(s) + ft_strlen(iter) - 2 + 1)));
	i = -1;
	j = -1;
	while (s[++i] && i != idx)
		ns[i] = s[i];
	while (iter && iter[++j])
		ns[i++] = iter[j];
	j = i - j + 2;
	while (s[j])
		ns[i++] = s[j++];
	return (ns);
}
