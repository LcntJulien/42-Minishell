/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 14:07:15 by jlecorne          #+#    #+#             */
/*   Updated: 2023/08/02 17:12:36 by jlecorne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	if (s)
	{
		while (s[i])
			i++;
		return (i);
	}
	return (0);
}
