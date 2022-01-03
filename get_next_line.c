/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraets <mbraets@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 12:37:31 by mbraets           #+#    #+#             */
/*   Updated: 2022/01/03 14:54:05 by mbraets          ###   ########.fr       */
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
	save = ft_strncpy(save, buffer, len);
	line = ft_strjoin(line, save);
	free(save);
	return (line);
}

char	*while_read(char *buffer, int count, int fd, int len)
{
	char	*line;
	int		index;

	line = NULL;
	while (count || buffer[0] != '\0')
	{
		buffer[count + len] = '\0';
		index = ft_str_eol(buffer);
		if (index == -1)
		{
			line = linejoin(buffer, line, len + count);
			if (!line)
				return (NULL);
			count = read(fd, buffer, BUFFER_SIZE);
			len = 0;
		}
		else
		{
			line = linejoin(buffer, line, index + 1);
			if (!line)
				return (NULL);
			ft_strncpy(buffer, buffer + index + 1, BUFFER_SIZE - index - 1);
			return (line);
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

	line = NULL;
	len = ft_strlen(buffer);
	if (fd < 0)
		return (NULL);
	count = read(fd, buffer + len, BUFFER_SIZE - len);
	if (count == -1)
		return (NULL);
	line = while_read(buffer, count, fd, len);
	return (line);
}

// void gnl(int fd, char const *str)
// {
// 	static int i;
// 	printf("Test %d\n", ++i);
// 	char *s = get_next_line(fd);
// 	// if (s == str)
// 		printf("%s%s", s, str);
// 	// else
// 	// 	printf("false, %s != %s", s, str);
// }
// #include <fcntl.h>
// int main(int argc, char **argv)
// {
// 	char *s;
// 	int fd;
// 	if (argc > 1)
// 	{

// 			fd = open("gnlTester/files/43_with_nl", 0);
// 			gnl(fd, "012345678901234567890123456789012345678901\n");
// 			gnl(fd, "2");
// 			gnl(fd, NULL);
// 			close(fd);
// 			return (0);
		
// 		fd = open(argv[1], 0);
// 		while ((s = get_next_line(fd)) && *s != '\0')
// 		{
// 			printf("%p: %s", s, s);
// 			free(s);
// 		}
// 	}
// 	else
// 	{
// 		fd = open("blanks", 0);
// 		s = get_next_line(fd);
// 		printf("%s", s);
// 		// free(s);
// 	}
// 	// while (1)
// 		// ;
// 	return (0);
// }