/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoppy <hoppy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 09:59:35 by hoppy             #+#    #+#             */
/*   Updated: 2022/01/11 10:07:22 by hoppy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
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
	static char	buffer[256][BUFFER_SIZE + 1];
	int			count;
	char		*line;
	int			len;

	if (fd < 0)
		return (NULL);
	len = ft_strlen(buffer[fd]);
	count = read(fd, buffer[fd] + len, BUFFER_SIZE - len);
	if (count == -1)
		return (NULL);
	line = while_read(buffer[fd], count, fd, len);
	return (line);
}
