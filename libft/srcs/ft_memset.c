/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 14:28:40 by jlecorne          #+#    #+#             */
/*   Updated: 2023/05/04 20:35:08 by jlecorne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	char	*s;

	s = b;
	while (len)
	{
		*s = (unsigned char)c;
		s++;
		len--;
	}
	return (b);
}
