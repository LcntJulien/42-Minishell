/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 15:08:47 by jlecorne          #+#    #+#             */
/*   Updated: 2023/09/22 12:50:05 by jlecorne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	*get_vname(char *s, int idx)
{
	char	*var;
	int		len;
	int		i;

	var = NULL;
	len = 0;
	i = idx;
	while (s[++i])
	{
		if (!s[i] || s[i] == ' ' || s[i] == '\'' || s[i] == '\"' || s[i] == '$'
			|| s[i] == '=')
			break ;
		len++;
	}
	var = ft_substr(s, (idx + 1), len);
	return (var);
}

static char	*env_var(t_shell *mini, t_token *tk, char **iter, int i)
{
	char	*cur;
	char	*tmp;

	cur = get_vname(tk->s, i);
	*iter = get_nvar(mini, cur);
	tmp = rewrite(mini, tk->s, cur, i);
	free(cur);
	return (tmp);
}

static char	*static_var(t_shell *mini, t_token *tk, char **iter, int i)
{
	char	*cur;
	char	*tmp;

	cur = get_vname(tk->s, i);
	*iter = other_variable(mini, tk, i + 1);
	tmp = rewrite2(tk->s, *iter, i);
	free(cur);
	return (tmp);
}

void	convert_var(t_shell *mini, t_token *tk)
{
	char	*tmp;
	char	*iter;
	int		i;

	tmp = NULL;
	iter = NULL;
	i = -1;
	while (tk->s && tk->s[++i])
	{
		if (tk->s[i] == '$' && tk->s[i + 1] != ' ' && !(is_quote(tk->s)
				&& quote_state(tk->s, i) == 1))
		{
			if (tk->s[i + 1] != '$' && tk->s[i + 1] != '?')
				tmp = env_var(mini, tk, &iter, i);
			else
				tmp = static_var(mini, tk, &iter, i);
			free(tk->s);
			tk->s = tmp;
			i += (ft_strlen(iter) - 1);
			free(iter);
		}
	}
}

int	contain_var(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == '$' && s[i + 1] && s[i + 1] != ' ' && s[i + 1] != '$' && s[i
				+ 1] != '_' && s[i + 1] != '?')
			return (1);
		else if (s[i] == '$' && s[i + 1] && (s[i + 1] == '$' || s[i + 1] == '_'
				|| s[i + 1] == '?'))
			return (1);
	}
	return (0);
}
