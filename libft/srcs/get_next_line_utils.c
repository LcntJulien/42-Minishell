/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 09:34:46 by jmathieu          #+#    #+#             */
/*   Updated: 2023/06/23 08:35:05 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_clr(t_list **retain, int i)
{
	t_list	*tmp;

	if (retain)
	{
		if (i == 0)
		{
			while (*retain)
			{
				tmp = (*retain)->next;
				if ((*retain)->content)
					free((*retain)->content);
				free(*retain);
				*retain = tmp;
			}
		}
		if (i == 1)
		{
			tmp = (*retain)->next;
			if ((*retain)->content)
				free((*retain)->content);
			free(*retain);
			*retain = tmp;
		}
	}
	return (NULL);
}

void	ft_clear(t_list **retain)
{
	char	*last;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (*retain)
	{
		while ((*retain)->next)
			ft_clr(retain, 1);
		while (((char *)(*retain)->content)[i]
			&& ((char *)(*retain)->content)[i] != '\n')
			i++;
		if (((char *)(*retain)->content)[i] == '\n')
			i++;
		last = malloc(sizeof(char) * (BUFFER_SIZE - i + 1));
		if (!last && ft_clr(retain, 0) == NULL)
			return ;
		while (((char *)(*retain)->content)[i])
			last[j++] = ((char *)(*retain)->content)[i++];
		last[j] = 0;
		free((*retain)->content);
		(*retain)->content = last;
	}
}
