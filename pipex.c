/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvergnas <lvergnas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 13:49:25 by lvergnas          #+#    #+#             */
/*   Updated: 2023/03/01 15:37:02 by lvergnas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>
//https://www.geeksforgeeks.org/c-program-demonstrate-fork-and-pipe/
//https://www.geeksforgeeks.org/difference-fork-exec/?ref=rp
int main(int argc, char **argv)
{
	int		fd;
	char	*file1;
	char 	*buf;

	if (argc != 2)
	{
		printf("Error, the number of arguments is incorrect");
		return (0);
	}
	fd =  open(argv[1], O_RDONLY);
	file1 = (char *)malloc(BUFFERSIZE * sizeof(char));
	if (!file1)
		return (0);
	buf = (char *)malloc(BUFFERSIZE * sizeof(char));
	if (!buf)
		return (0);
	while (read(fd, buf, BUFFERSIZE) != 0)
	{	
		file1 = ft_strjoin(file1, buf);
	}
	printf("%s\nfin\n", file1);
	return (0);
}