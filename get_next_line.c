/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabdul-s <fabdul-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 10:50:18 by fabdul-s          #+#    #+#             */
/*   Updated: 2026/02/02 16:44:47 by fabdul-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_from_file(int fd, char *remainder, char *buffer)
{
	int		rlen;
	char	*temp;

	rlen = 1;
	while (rlen > 0 && !ft_strchr(remainder, '\n'))
	{
		rlen = read(fd, buffer, BUFFER_SIZE);
		if (rlen == -1)
		{
			free(remainder);
			return (NULL);
		}
		else if (rlen == 0)
			break ;
		buffer[rlen] = '\0';
		temp = remainder;
		remainder = ft_strjoin(temp, buffer);
		free(temp);
	}
	return (remainder);
}

static char	*extract_line(char *remainder)
{
	size_t	i;

	i = 0;
	if (!remainder)
		return (NULL);
	while (remainder[i] && remainder[i] != '\n')
		i++;
	if (remainder[i] == '\n')
		i++;
	return (ft_substr(remainder, 0, i));
}

static char	*remove_unwanted(char *remainder)
{
	char	*new_remainder;
	size_t	i;

	i = 0;
	while (remainder[i] && remainder[i] != '\n')
		i++;
	if (!remainder[i])
	{
		free(remainder);
		return (NULL);
	}
	i++;
	new_remainder = ft_strdup(remainder + i);
	free(remainder);
	return (new_remainder);
}

char	*get_next_line(int fd)
{
	static char	*remainder;
	char		*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= INT_MAX)
		return (NULL);
	if (!remainder)
		remainder = ft_strdup("");
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	remainder = read_from_file(fd, remainder, buffer);
	free(buffer);
	if (!remainder || *remainder == '\0')
	{
		free(remainder);
		remainder = NULL;
		return (NULL);
	}
	line = extract_line(remainder);
	remainder = remove_unwanted(remainder);
	return (line);
}
