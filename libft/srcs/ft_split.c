/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:43:56 by jlecorne          #+#    #+#             */
/*   Updated: 2023/05/04 20:35:02 by jlecorne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	tabcounter(const char *s, char c)
{
	int	i;
	int	r;

	i = 0;
	r = 0;
	if (c == 0)
		return (1);
	while (s[i])
	{
		if (s[i] != 0 && s[i] != c && (i == 0 || s[i - 1] == c))
			r++;
		i++;
	}
	return (r);
}

char	**freetab(char **p)
{
	int	i;

	i = 0;
	while (p[i])
	{
		free(p[i]);
		i++;
	}
	free(p[i]);
	free(p);
	return (NULL);
}

char	*filltab(const char *s, char c)
{
	int		i;
	char	*ptr;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	ptr = malloc(sizeof(char) * (i + 1));
	if (!ptr)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != c)
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = 0;
	return (ptr);
}

char	**ft_split(const char *s, char c)
{
	int		i;
	int		j;
	char	**tab;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	tab = malloc(sizeof(char *) * (tabcounter(s, c) + 1));
	if (!tab)
		return (NULL);
	while (s[i])
	{
		if ((i == 0 && s[i] != c) || (s[i] != c && s[i - 1] == c))
		{
			tab[j] = filltab((s + i), c);
			if (!tab[j])
				return (freetab(tab));
			j++;
			i++;
		}
		i++;
	}
	tab[j] = 0;
	return (tab);
}
