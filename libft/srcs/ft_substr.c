/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 09:47:21 by jlecorne          #+#    #+#             */
/*   Updated: 2023/08/02 17:12:27 by jlecorne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*p;
	int		size;

	i = 0;
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (len < ft_strlen(s + start))
		size = len;
	else
		size = ft_strlen(s + start);
	p = malloc(sizeof(char) * (size + 1));
	if (!p)
		return (NULL);
	while (*(s + start) && i < len)
	{
		*(char *)(p + i) = *(char *)(s + start);
		start++;
		i++;
	}
	p[i] = '\0';
	return (p);
}
