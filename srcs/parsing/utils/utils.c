/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 18:45:51 by jlecorne          #+#    #+#             */
/*   Updated: 2023/08/24 11:46:29 by jlecorne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	str_alloc(char *s, int *idx)
{
	int	i;

	i = 0;
	while (s[*idx + i])
	{
		if (s[*idx + i] == ' ' && quote_state(s, (*idx + i)) == 0)
			break ;
		i++;
	}
	return (i);
}

int	clean_alloc(char *s)
{
	int	i;
	int	r;

	i = -1;
	r = 0;
	while (s[++i])
	{
		if (s[i] != '\'' && s[i] != '\"')
			r++;
		else if (quote_state(s, i) && ((s[i] == '\'' && quote_state(s, i) == 2)
				|| (s[i] == '\"' && quote_state(s, i) == 1)))
			r++;
	}
	return (r + 1);
}

char	*clean_s(char *s)
{
	char	*new;
	int		i;
	int		j;

	i = -1;
	j = 0;
	new = ft_calloc(sizeof(char), clean_alloc(s));
	if (!new)
		return (NULL);
	while (s[++i])
	{
		if (s[i] != '\'' && s[i] != '\"')
			new[j++] = s[i];
		else if (quote_state(s, i) && ((s[i] == '\'' && quote_state(s, i) == 2)
				|| (s[i] == '\"' && quote_state(s, i) == 1)))
			new[j++] = s[i];
	}
	return (new);
}
