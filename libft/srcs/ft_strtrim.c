/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 11:44:49 by jlecorne          #+#    #+#             */
/*   Updated: 2023/05/04 20:34:53 by jlecorne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static int	checkset(char c, const char *set)
{
	while (*set)
	{
		if (c == *set++)
			return (1);
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	char	*p;

	i = 0;
	j = ft_strlen(s1);
	if (s1 != 0)
	{
		while (*(s1 + i) && checkset(*(s1 + i), set))
			i++;
		if (i == j)
			return (p = ft_strdup(""));
		while (checkset(*(s1 + j - 1), set) && *(s1 + j - 1))
			j--;
		return (p = ft_substr(s1, i, (j - i)));
	}
	return (0);
}
