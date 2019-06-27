/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vesingh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 08:28:55 by vesingh           #+#    #+#             */
/*   Updated: 2019/06/27 15:28:04 by vesingh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_storetoline(char **store, char **line)
{
	int	len;
	char *temp;
	
	if (ft_strchr(*store, '\n'))
	{
		len = ft_strchr(*store, '\n') - *store;
		*line = ft_strsub(*store, 0, len);
		temp = ft_strchr(*store, '\n') + 1;
		temp = ft_strdup(temp);
		ft_strdel(store);
		*store = ft_strdupdel(&temp);
		if (*store[0] == '\0')
			ft_strdel(store);
	}
	else if (ft_strchr(*store, '\0'))
	{
		*line = ft_strdupdel(store);
	}
	return (1);
}

int			get_next_line(const int fd, char **line)
{
	static char	*store[255];
	char		buff[BUFF_SIZE + 1];
	int			n;

	if (fd < 0 || line == NULL || BUFF_SIZE < 0)
		return (-1);
	if (!store[fd])
		store[fd] = ft_strnew(0);
	while ((n = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[n] = '\0';
		store[fd] = ft_strjoinfree(store[fd], buff);
		if (ft_strchr(store[fd], '\n'))
			break ; 
	}
	if (n < 0)
		return (-1);
	else if (n == 0 && (store[fd] == NULL || store[fd][0] == '\0'))
		return (0);
	else 
		return(ft_storetoline(&store[fd], line));
	return (0);
}
