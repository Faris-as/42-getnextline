/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabdul-s <fabdul-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 10:50:52 by fabdul-s          #+#    #+#             */
/*   Updated: 2025/12/22 03:11:20 by fabdul-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*read_from_file(int fd, char *remainder, char *buffer)
{
	int		rlen;
	char	*temp;

	rlen = 1;
	while (rlen > 0)
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
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (remainder);
}

static char	*extract_line(char *remainder)
{
	size_t	i;

	i = 0;
	if (!remainder[i])
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
	static char	*remainder[OPEN_MAX];
	char		*buffer;
	char		*temp;

	if (fd < 0 || fd >= OPEN_MAX || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	if (!remainder[fd])
		remainder[fd] = ft_strdup("");
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	remainder[fd] = read_from_file(fd, remainder[fd], buffer);
	free(buffer);
	if (!remainder[fd] || *remainder[fd] == '\0')
	{
		free(remainder[fd]);
		remainder[fd] = NULL;
		return (NULL);
	}
	temp = extract_line(remainder[fd]);
	remainder[fd] = remove_unwanted(remainder[fd]);
	return (temp);
}
