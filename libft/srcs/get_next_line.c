/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 14:15:32 by jmathieu          #+#    #+#             */
/*   Updated: 2023/06/23 08:35:13 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_len(t_list *retain)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!retain)
		return (0);
	while (retain->next)
	{
		while (((char *)retain->content)[i])
			i++;
		retain = retain->next;
		j += i;
		i = 0;
	}
	while (((char *)retain->content)[i] && ((char *)retain->content)[i] != '\n')
		i++;
	if (((char *)retain->content)[i] == '\n')
		i++;
	j += i;
	return (j);
}

char	*ft_extract(t_list *retain)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!retain)
		return (0);
	line = malloc(sizeof(char) * (ft_len(retain) + 1));
	if (!line)
		return (0);
	while (retain->next)
	{
		while (((char *)retain->content)[i])
			line[j++] = ((char *)retain->content)[i++];
		retain = retain->next;
		i = 0;
	}
	while (((char *)retain->content)[i] && ((char *)retain->content)[i] != '\n')
		line[j++] = ((char *)retain->content)[i++];
	if (((char *)retain->content)[i] == '\n')
		line[j++] = '\n';
	line[j] = 0;
	return (line);
}

int	ft_read(t_list **retain, int fd)
{
	t_list	*tmp;
	char	*buffer;
	int		seen;

	seen = 0;
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (-1);
	seen = read(fd, buffer, BUFFER_SIZE);
	if (seen > 0)
	{
		buffer[seen] = 0;
		tmp = ft_lstnew(buffer);
		if (!tmp)
		{
			ft_clr(retain, 0);
			free(buffer);
			return (-1);
		}
		ft_lstadd_back(retain, tmp);
	}
	else
		free(buffer);
	return (seen);
}

int	ft_newline(t_list *retain)
{
	int		i;
	t_list	*last;

	i = 0;
	if (!retain)
		return (0);
	last = ft_lstlast(retain);
	while (((char *)last->content)[i])
	{
		if (((char *)last->content)[i++] == '\n')
			return (1);
	}
	return (0);
}

char	*get_next_line(int fd)
{
	static t_list	*retain;
	char			*line;
	int				seen;

	seen = 1;
	line = NULL;
	if (BUFFER_SIZE <= 0 || fd < 0 || read(fd, line, 0) == -1)
		return (ft_clr(&retain, 0));
	while (!ft_newline(retain) && seen > 0)
	{
		seen = ft_read(&retain, fd);
		if (seen == -1)
			return (ft_clr(&retain, 0));
	}
	line = ft_extract(retain);
	if (!line || line[0] == 0)
	{
		if (line)
			free(line);
		return (ft_clr(&retain, 0));
	}
	ft_clear(&retain);
	return (line);
}
