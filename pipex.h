/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvergnas <lvergnas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 13:49:27 by lvergnas          #+#    #+#             */
/*   Updated: 2023/10/06 12:17:16 by lvergnas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>		//open
# include <stdlib.h>	//malloc/free/exit
# include <unistd.h>	//read/write
# include <sys/wait.h>	//wait
# include <string.h>	//strerror
# include <stdio.h>		//perror/printf

typedef struct s_pipex
{
	pid_t	pid;
	int		pipefd[2];
	int		in_fd;
	int		out_fd;
	char	*cmd;
	char	*env_path;
	char	**them_paths;
	char	**cmd_args;
}t_pipex;

size_t	ft_strlen(const char *str);
char	*ft_strjoin(char *s1, char *s2);
char	**ft_split(char *s, char c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		msg_error(char *error_type);
void	free_child(t_pipex *pipex);
void	free_all(t_pipex *pipex);

#endif