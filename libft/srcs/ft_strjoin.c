/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 11:15:03 by jlecorne          #+#    #+#             */
/*   Updated: 2023/06/12 19:55:19 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	int		len;
	char	*p;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	j = 0;
	len = (ft_strlen(s1) + ft_strlen(s2) + 1);
	p = malloc(sizeof(char) * len);
	if (!p)
		return (0);
	while (s1[i])
	{
		p[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		p[i + j] = s2[j];
		j++;
	}
	p[i + j] = '\0';
	return (p);
}
