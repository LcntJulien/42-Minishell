/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 11:24:32 by jlecorne          #+#    #+#             */
/*   Updated: 2023/05/04 20:35:20 by jlecorne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	sizenbr(long nbr)
{
	size_t	r;

	r = 0;
	if (nbr < 0)
	{
		nbr *= -1;
		r++;
	}
	while (nbr >= 1)
	{
		r++;
		nbr /= 10;
	}
	return (r);
}

char	*convertnbr(long nbr, int len, int sign, char *s)
{
	if (nbr == 0)
		return (s = ft_strdup("0"));
	s = malloc(sizeof(char) * (len + 1));
	if (!s)
		return (NULL);
	if (nbr < 0)
	{
		nbr *= -1;
		sign = 1;
	}
	s[len] = '\0';
	while (--len >= 0)
	{
		s[len] = (nbr % 10) + '0';
		nbr /= 10;
	}
	if (sign == 1)
		s[len - len] = '-';
	return (s);
}

char	*ft_itoa(int n)
{
	long	nbr;
	int		i;
	int		j;
	char	*s;
	char	*r;

	nbr = n;
	i = sizenbr(nbr);
	j = 0;
	s = 0;
	r = convertnbr(nbr, i, j, s);
	if (!r)
		return (NULL);
	return (r);
}
