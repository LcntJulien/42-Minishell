/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_history.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 16:17:11 by jmathieu          #+#    #+#             */
/*   Updated: 2023/08/31 14:52:03 by jlecorne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	add_histo(char *str, int histo)
{
	histo = open(".mini_history", O_RDWR | O_APPEND | O_CREAT, 0644);
	add_history(str);
	if (histo <= 0)
		return ;
	write(histo, str, ft_strlen(str));
	write(histo, "\n", 1);
	close(histo);
}

static int	init_history(int *histo)
{
	char	*str;
	char	*s;

	str = get_next_line(*histo);
	if (!str)
		return (0);
	while (str)
	{
		s = ft_substr(str, 0, ft_strlen(str) - 1);
		add_history(s);
		free(str);
		free(s);
		str = get_next_line(*histo);
	}
	return (1);
}

int	create_history(int *histo)
{
	*histo = open(".mini_history", O_RDWR | O_APPEND | O_CREAT, 0644);
	if (*histo == -1)
	{
		ft_putstr_fd("Fail to initiate history\n", 2);
		return (0);
	}
	init_history(histo);
	close(*histo);
	return (1);
}
