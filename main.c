/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabdul-s <fabdul-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 01:38:41 by fabdul-s          #+#    #+#             */
/*   Updated: 2025/12/22 01:38:42 by fabdul-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int	main(void)
{
	int		fd;
	char	*line;
	int		count;

	fd = open("hello.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("Error opening file\n");
		return (1);
	}
	count = 0;
	line = get_next_line(fd);
	printf("Line %d: %s \n", ++count, line);
	line = get_next_line(fd);
	printf("Line %d: %s", ++count, line);
	free(line);
	close(fd);
	return (0);
}
