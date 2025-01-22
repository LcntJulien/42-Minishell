/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 18:18:34 by jlecorne          #+#    #+#             */
/*   Updated: 2023/05/04 20:34:56 by jlecorne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*r;
	int		i;

	i = 0;
	r = ft_strdup(s);
	if (!r)
		return (NULL);
	while (r[i])
	{
		r[i] = (*f)(i, r[i]);
		i++;
	}
	return (r);
}
