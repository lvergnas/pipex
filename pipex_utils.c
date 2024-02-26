/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvergnas <lvergnas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 14:39:37 by lvergnas          #+#    #+#             */
/*   Updated: 2023/10/06 13:48:55 by lvergnas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

size_t	ft_strlen(const char *str)
{
	unsigned int	index;

	if (!str)
		return (0);
	index = 0;
	while (((char *)str)[index])
		index++;
	return (index);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char			*str;
	unsigned int	index;
	unsigned int	indexs2;
	size_t			lentotal;

	if (!s1 || !s2)
		return (0);
	lentotal = ft_strlen(s1) + ft_strlen(s2) + 1;
	str = (char *)malloc(lentotal);
	if (!str)
		return (str);
	index = 0;
	indexs2 = 0;
	while (index < lentotal)
	{
		if (index < ft_strlen(s1))
			str[index] = s1[index];
		else
		{
			str[index] = s2[indexs2];
			indexs2++;
		}
		index++;
	}
	return (str);
}

int	msg_error(char *error_type)
{
	perror(error_type);
	exit(EXIT_FAILURE);
}

void	free_child(t_pipex *pipex)
{
	int	i;

	i = -1;
	while (pipex->cmd_args[++i])
		free (pipex->cmd_args[i]);
	free(pipex->cmd_args);
	free(pipex->cmd);
}

void	free_all(t_pipex *pipex)
{
	int	i;

	close(pipex->in_fd);
	close(pipex->out_fd);
	i = -1;
	while (pipex->them_paths[++i])
		free(pipex->them_paths[i]);
	free(pipex->them_paths);
}
