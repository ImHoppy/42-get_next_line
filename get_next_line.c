/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraets <mbraets@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 12:37:31 by mbraets           #+#    #+#             */
/*   Updated: 2021/12/22 17:38:41 by mbraets          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_line();

char	*save_line(char *save, char *buffer);

#include <stdio.h>
char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	int			count;
	char		*line;
	char		*save;
	int			len;
	int			index;

	line = "";
	len = ft_strlen(buffer);
	if (fd < 0)
		return (NULL);
	count = read(fd, buffer + len, BUFFER_SIZE - len);
	// printf("%d %d\n", len, count);
	if (count == -1)
		return (NULL);
	printf("{%d %d}{%s}\n", count, buffer[0] != '\0', buffer);
	while (count || buffer[0] != '\0')
	{
		//printf("buff:%s line:%s save:%s", buffer, line, save);
		buffer[count] = '\0';
		index = ft_str_eol(buffer);
		if (index == -1)
		{
			save = malloc(sizeof(char) * (len + count + 1));
			if (!save)
				return (NULL);
			save = ft_strncpy(save, buffer, len + count);
			printf("%s", line);
			line = ft_strjoin(line, save);
			count = read(fd, buffer, BUFFER_SIZE);
			len = 0;
			printf("here\n");
		}
		else
		{
			save = malloc(sizeof(char) + (index + 2));
			if (!save)
				return (NULL);
			// printf("\np: %s/%s/%s", save, buffer, line);
			save = ft_strncpy(save, buffer, index + 1);
			// printf("\np: %s/%s/%s", save, buffer, line);
			line = ft_strjoin(line, save);
			// printf("\np: %s/%s/%s", save, buffer, line);
			ft_strncpy(buffer, buffer + index + 1, BUFFER_SIZE - index - 1);
			printf("[%s]\n", buffer);
			return (line);
		}
	}
	return (line);
}
#include <fcntl.h>
int main(int argc, char **argv)
{
	char *s;
	int fd;
	if (argc > 1)
	{
		fd = open(argv[1], 0);
		while ((s = get_next_line(fd)) && *s != '\0')
		{
			printf("%p: %s", s, s);
			free(s);
		}
	}
	else
	{
		fd = open("blanks", 0);
		s = get_next_line(fd);
		printf("%s", s);
		// free(s);
	}
	// while (1)
	// 	;
	return (0);
}