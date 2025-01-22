/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 17:50:18 by jlecorne          #+#    #+#             */
/*   Updated: 2023/09/20 22:58:53 by jlecorne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	*fill1(const char *s, int q, int sw)
{
	int		i;
	char	*ptr;

	i = 1;
	while (s[i] && s[i + 1] != q)
		i++;
	if (sw == 1)
		i++;
	ptr = ft_calloc((i + 1), sizeof(char));
	i = 1;
	while (s[i] && s[i] != q)
	{
		ptr[i - 1] = s[i];
		i++;
	}
	if (sw == 1)
		ptr[++i] = '/';
	ptr[++i] = 0;
	return (ptr);
}

char	*fill2(const char *s, char c, int sw)
{
	int		i;
	char	*ptr;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	if (sw == 1)
		i++;
	ptr = ft_calloc((i + 1), sizeof(char));
	i = 0;
	while (s[i] && s[i] != c)
	{
		ptr[i] = s[i];
		i++;
	}
	if (sw == 1)
		ptr[i++] = '/';
	ptr[i] = 0;
	return (ptr);
}

char	*fill(const char *s, char c, int q, int sw)
{
	char	*ptr;

	if (q > 0)
		ptr = fill1(s, q, sw);
	else
		ptr = fill2(s, c, sw);
	return (ptr);
}

char	**tab_maker(const char *s, char c, int q, int sw)
{
	int		i;
	int		j;
	char	**tab;

	i = 0;
	j = 0;
	tab = ft_calloc((scount(s, c, q) + 1), sizeof(char *));
	while (s[i])
	{
		if (s[i] && s[i] != c && q == 0 && (i == 0 || s[i - 1] == c))
		{
			if (s[i] == 34 || s[i] == 39)
				q = s[i];
			tab[j] = fill((s + i), c, q, sw);
			if (!tab[j])
				return (tabfree(tab));
			j++;
		}
		i++;
		if (s[i] == q)
			q = 0;
	}
	tab[j] = 0;
	return (tab);
}

char	**custom_split(const char *s, char c, int sw)
{
	int		q;
	char	**tab;

	if (!s)
		return (NULL);
	q = 0;
	tab = tab_maker(s, c, q, sw);
	return (tab);
}
