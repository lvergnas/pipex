/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvergnas <lvergnas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 13:49:25 by lvergnas          #+#    #+#             */
/*   Updated: 2023/10/06 13:48:16 by lvergnas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*find_path_in_env(char **env)
{
	int	i; 

	i = -1;
	while (env[++i])
	{
		if (env[i][0] == 'P' & env[i][1] == 'A' & env[i][2] == 'T')
		{
			return (env[i] + 5);
		}
	}
	return (NULL);
}

static char	*get_cmd(char **them_paths, char *cmd)
{
	int		i;
	char	*cmd_temp;
	char	*real_cmd;

	i = -1;
	while (them_paths[++i])
	{
		cmd_temp = ft_strjoin(them_paths[i], "/");
		real_cmd = ft_strjoin(cmd_temp, cmd);
		free(cmd_temp);
		if (access(real_cmd, F_OK) == 0)
			return (real_cmd);
		free(real_cmd);
	}
	return (NULL);
}

static int	exec_child1(t_pipex pipex, char **argv, char **env)
{
	dup2(pipex.pipefd[1], STDOUT_FILENO);
	close(pipex.pipefd[0]);
	dup2(pipex.in_fd, STDIN_FILENO);
	pipex.cmd_args = ft_split(argv[2], ' ');
	pipex.cmd = get_cmd(pipex.them_paths, pipex.cmd_args[0]);
	if (!pipex.cmd)
	{
		free_child(&pipex);
		return (msg_error("command not found"));
	}
	return (execve(pipex.cmd, pipex.cmd_args, env));
}

static int	exec_child2(t_pipex pipex, char **argv, char **env)
{
	dup2(pipex.pipefd[0], STDIN_FILENO);
	close(pipex.pipefd[1]);
	dup2(pipex.out_fd, STDOUT_FILENO);
	pipex.cmd_args = ft_split(argv[3], ' ');
	pipex.cmd = get_cmd(pipex.them_paths, pipex.cmd_args[0]);
	if (!pipex.cmd)
	{
		free_child(&pipex);
		return (msg_error("command not found"));
	}
	return (execve(pipex.cmd, pipex.cmd_args, env));
}

int	main(int argc, char **argv, char **env)
{
	t_pipex	pipex;

	if (argc != 5)
		return (msg_error("Argument error"));
	if (ft_strncmp(argv[1] + (ft_strlen(argv[1]) - 4), ".txt", 4) == 0)
		pipex.in_fd = open(argv[1], O_RDONLY);
	if (pipex.in_fd < 0)
		return (msg_error("Error infile"));
	pipex.out_fd = open(argv[argc - 1], O_TRUNC | O_CREAT | O_RDWR, 0666);
	if (pipex.out_fd < 0)
		return (msg_error("Error outfile"));
	pipex.env_path = find_path_in_env(env);
	pipex.them_paths = ft_split(pipex.env_path, ':');
	pipe(pipex.pipefd);
	pipex.pid = fork();
	if (pipex.pid == 0)
		exec_child1(pipex, argv, env);
	waitpid(pipex.pid, NULL, 0);
	close(pipex.pipefd[1]);
	pipex.pid = fork();
	if (pipex.pid == 0)
		exec_child2(pipex, argv, env);
	waitpid(pipex.pid, NULL, 0);
	free_all(&pipex);
	return (0);
}
