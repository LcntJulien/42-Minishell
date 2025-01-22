/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 17:18:46 by jlecorne          #+#    #+#             */
/*   Updated: 2023/05/04 20:35:14 by jlecorne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*elem;
	void	*tmp;

	if (!lst)
		return (0);
	new_lst = 0;
	while (lst)
	{
		tmp = f(lst->content);
		elem = ft_lstnew(tmp);
		if (!elem)
		{
			ft_lstclear(&new_lst, del);
			free(tmp);
			return (0);
		}
		ft_lstadd_back(&new_lst, elem);
		lst = lst->next;
	}
	return (new_lst);
}
