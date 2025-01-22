/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 15:15:41 by jlecorne          #+#    #+#             */
/*   Updated: 2023/09/22 12:45:41 by jlecorne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	*get_nvar(t_shell *mini, char *vname)
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
	if (mini->env)
	{
		while (mini->env[++i])
		{
			if (ft_strncmp(tmp, mini->env[i], ft_strlen(tmp)) == 0)
			{
				nvar = ft_substr(mini->env[i], (ft_strlen(vname) + 1),
						ft_strlen(mini->env[i]) - (ft_strlen(vname) + 1));
			}
		}
	}
	free(tmp);
	return (nvar);
}

char	*get_ns(char *s, char *nvar, int idx, int vname_len)
{
	char	*ns;
	int		i;
	int		j;

	ns = NULL;
	i = -1;
	j = -1;
	if ((ft_strlen(s) + ft_strlen(nvar) - vname_len) == 0)
		return (NULL);
	ns = ft_calloc(sizeof(char), ((ft_strlen(s) + ft_strlen(nvar)) - vname_len)
			+ 1);
	while (s[++i] && i != idx)
		ns[i] = s[i];
	while (nvar && nvar[++j])
		ns[i + j] = nvar[j];
	if (!nvar)
		j++;
	j += i;
	while (s[++i] && s[i] != ' ' && s[i] != '\'' && s[i] != '\"' && s[i] != '$'
		&& s[i] != '=')
		;
	while (s[i])
		ns[j++] = s[i++];
	return (ns);
}

char	*rewrite(t_shell *mini, char *s, char *vname, int idx)
{
	char	*nvar;
	char	*ns;
	int		i;

	nvar = get_nvar(mini, vname);
	ns = NULL;
	i = idx;
	while (s[++i] && s[i] != ' ' && s[i] != '\'' && s[i] != '\"' && s[i] != '$'
		&& s[i] != '=')
		;
	i -= idx;
	ns = get_ns(s, nvar, idx, i);
	free(nvar);
	return (ns);
}
