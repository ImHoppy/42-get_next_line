/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraets <mbraets@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 12:37:31 by mbraets           #+#    #+#             */
/*   Updated: 2021/12/21 18:59:54 by mbraets          ###   ########.fr       */
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
			ft_strncpy(save, buffer, len + count);
			line = ft_strjoin(line, save);
			count = read(fd, buffer, BUFFER_SIZE);
			len = 0;
		}
		else
		{
			save = malloc(sizeof(char) + (index + 2));
			if (!save)
				return (NULL);
			save = ft_strncpy(save, buffer, index + 1);
			line = ft_strjoin(line, save);
			ft_strncpy(buffer, buffer + index + 1, BUFFER_SIZE - index - 1);
			return (line);
		}
	}
	return (line);
}
// #include <fcntl.h>
// int main(int argc, char **argv)
// {
// 	char *s;
// 	int fd;
// 	if (argc > 1)
// 	{
// 		fd = open(argv[1], 0);
// 		while ((s = get_next_line(fd)) && *s != '\0')
// 		{
// 			printf("%p: %s", s, s);
// 			//free(s);
// 		}
// 	}
// 	else
// 	{
// 		fd = open("blanks", 0);
// 		s = get_next_line(fd);
// 		printf("%s", s);
// 		// free(s);
// 	}
// 	return (0);
// }