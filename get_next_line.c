/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraets <mbraets@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 12:37:31 by mbraets           #+#    #+#             */
/*   Updated: 2022/01/10 07:44:59 by mbraets          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*linejoin(char *buffer, char *line, int len)
{
	char	*save;

	save = malloc(sizeof(char) * (len + 1));
	if (!save)
		return (NULL);
	ft_strncpy(save, buffer, len, NULL);
	line = ft_strjoin(line, save);
	free(save);
	return (line);
}

char	*while_read(char *b, int count, int fd, int len)
{
	char	*line;
	int		i;

	line = NULL;
	while (count || b[0] != '\0')
	{
		b[count + len] = '\0';
		i = ft_str_eol(b);
		if (i == -1)
		{
			line = linejoin(b, line, len + count);
			if (!line)
				return (NULL);
			count = read(fd, b, BUFFER_SIZE);
			len = 0;
		}
		else
		{
			line = linejoin(b, line, i + 1);
			if (!line)
				return (NULL);
			return (ft_strncpy(b, b + i + 1, BUFFER_SIZE - i - 1, line));
		}
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	int			count;
	char		*line;
	int			len;

	len = ft_strlen(buffer);
	if (fd < 0)
		return (NULL);
	count = read(fd, buffer + len, BUFFER_SIZE - len);
	if (count == -1)
		return (NULL);
	line = while_read(buffer, count, fd, len);
	return (line);
}
