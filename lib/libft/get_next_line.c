/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 15:40:51 by rhvidste          #+#    #+#             */
/*   Updated: 2025/01/22 17:43:37 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"

char		*get_next_line(int fd);
static char	*fill_line_buffer(int fd, char *stash, char *buffer);
static char	*set_line(char *line_buffer);
static char	*flush_stash(char *stash, char *buffer);

char	*get_next_line(int fd)
{
	char		*buffer;
	char		*line;
	static char	*stash;

	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free(stash);
		free(buffer);
		stash = NULL;
		buffer = NULL;
		return (NULL);
	}
	if (!buffer)
		return (NULL);
	line = fill_line_buffer(fd, stash, buffer);
	free(buffer);
	buffer = NULL;
	if (!line)
		return (NULL);
	stash = set_line(line);
	return (line);
}

static char	*set_line(char *line_buffer)
{
	char	*stash;
	ssize_t	i;

	i = 0;
	while (line_buffer[i] != '\n' && line_buffer[i] != '\0')
		i++;
	if (line_buffer[i] == 0 || line_buffer[1] == 0)
		return (NULL);
	stash = ft_substr(line_buffer, i + 1, ft_strlen(line_buffer) - i);
	if (*stash == 0)
	{
		free(stash);
		stash = NULL;
	}
	line_buffer[i + 1] = 0;
	return (stash);
}

static char	*fill_line_buffer(int fd, char *stash, char *buffer)
{
	ssize_t	byte_read;

	byte_read = 1;
	while (byte_read > 0)
	{
		byte_read = read(fd, buffer, BUFFER_SIZE);
		if (byte_read == -1)
		{
			free(stash);
			return (NULL);
		}
		else if (byte_read == 0)
		{
			break ;
		}
		buffer[byte_read] = 0;
		stash = flush_stash(stash, buffer);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (stash);
}

static char	*flush_stash(char *stash, char *buffer)
{
	char	*tmp;

	if (!stash)
		stash = ft_strdup("");
	tmp = stash;
	stash = ft_strjoin(tmp, buffer);
	free(tmp);
	tmp = NULL;
	return (stash);
}
