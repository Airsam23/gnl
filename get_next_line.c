/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sashamdi <sashamdi@student.42Berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 15:14:29 by sashamdi          #+#    #+#             */
/*   Updated: 2024/05/31 19:00:28 by sashamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
get_new_line_function extracts a complete line, 
including the newline character if present, 
from a provided buffer, 
dynamically allocates memory for it, 
and returns this newly formed string, 
*/
char	*get_new_line(char *remain)
{
	int		i;
	char	*line;

	i = 0;
	if (!remain[i])
		return (NULL);
	while (remain[i] && remain[i] != '\n')
		i++;
	line = (char *)malloc((sizeof(char)) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (remain[i] && remain[i] != '\n')
	{
		line[i] = remain[i];
		i++;
	}
	if (remain[i] == '\n')
	{
		line[i] = remain[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

/*
get_remain function processes the buffer
to remove the portion already read as a line, 
reallocates memory for the remainder of the buffer
starting after the newline character, 
and returns this new substring,
thus preparing the buffer for the next line retrieval
*/

char	*get_remain(char *remain)
{
	int		i;
	int		k;
	char	*buff;

	i = 0;
	while (remain[i] && remain[i] != '\n')
		i++;
	if (!remain[i])
	{
		free(remain);
		return (NULL);
	}
	buff = (char *)malloc(sizeof(char) * (ft_strlen(remain) - i + 1));
	if (!buff)
		return (NULL);
	i++;
	k = 0;
	while (remain[i])
		buff[k++] = remain[i++];
	buff[k] = '\0';
	free(remain);
	return (buff);
}

/*
get_buffer function reads data from a file descriptor into a buffer
until a newline is encountered or no more data is available,
concatenates this new data to any existing remnants in remain,
and returns the updated buffer
*/
char	*get_buffer(char *remain, int fd)
{
	char	*buff;
	int		size;

	buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	size = 1;
	while (!ft_strchr(remain, '\n') && size != 0)
	{
		size = read(fd, buff, BUFFER_SIZE);
		if (size == -1)
		{
			free(buff);
			free(remain);
			return (NULL);
		}
		buff[size] = '\0';
		remain = ft_strjoin(remain, buff);
	}
	free(buff);
	return (remain);
}

/*
The get_next_line function reads one line at a time from a file descriptor,
using a static buffer to keep leftover data between reads,and returns the line,
making it easy to read lines sequentially from a file or input source.
*/

char	*get_next_line(int fd)
{
	char		*line;
	static char	*remain;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		return (NULL);
	}
	remain = get_buffer(remain, fd);
	if (!remain)
	{
		return (NULL);
	}
	line = get_new_line(remain);
	remain = get_remain(remain);
	return (line);
}

/*int	main(void)
{
	int		fd1;
	char	*str;
	int		i;

	i = 0;
	fd1 = open("dict.txt", O_RDONLY);
	while (i < 5)
	{
		str = get_next_line(fd1);
		printf("%s", str);
		free(str);
		i++;
	}
	return (0);
}*/
