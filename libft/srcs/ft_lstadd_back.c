/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 16:11:46 by jlecorne          #+#    #+#             */
/*   Updated: 2023/06/23 08:46:20 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*t;

	if (lst)
	{
		if (*lst)
		{
			t = ft_lstlast(*lst);
			t->next = &*new;
		}
		else
			*lst = new;
	}
}
