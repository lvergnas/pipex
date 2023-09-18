/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvergnas <lvergnas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 13:49:27 by lvergnas          #+#    #+#             */
/*   Updated: 2023/09/18 12:18:55 by lvergnas         ###   ########.fr       */
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
	pid_t	pid1;
	pid_t	pid2;
	int		pipefd[2];
	int		in_fd;
	int		out_fd;
	char	*cmd;
	char	*path;
	char	**cmd_path;
	char	**cmd_args;
}t_pipex;

size_t	ft_strlen(const char *str);
char	*ft_strchr(char *str, int ch);
char	*ft_strjoin(char *s1, char *s2);
char	**ft_split(char *s, char c);
char	*ft_strtrim(char *s1, char const *set);
int		find_path_in_env(char **env, char *tofind);
void	*ft_calloc(size_t count, size_t size);

#endif