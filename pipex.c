/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loura <loura@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 13:49:25 by lvergnas          #+#    #+#             */
/*   Updated: 2023/09/27 12:16:50 by loura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*extract_cmd(char *raw_cmd)
{
	int		i;
	char	*cmd;

	i = 0;
	while (raw_cmd[i] != ' ')
		i++;
	cmd = malloc(sizeof(char) * (i + 2));
	if (!cmd)
		return (NULL);
	i = 0;
	cmd[i] = '/';
	while (raw_cmd[i] != ' ')
	{
		cmd[i + 1] = raw_cmd[i];
		i++;
	}
	cmd[i + 1] = '\0';
	return (cmd);
}

static char	*extract_args(char *raw_cmd, char *cmd)
{
	char	*args;

	args = ft_strtrim(raw_cmd, (const char *)cmd);
	if (args[0] != '\0')
	{
		args = ft_strtrim(args, " ");
		return (args);
	}
	free(args);
	return (NULL);
}

static char	*find_path(char **env, char *cmd)
{
	int		i;
	char	*path;
	char	**them_paths;

	path = ft_strtrim(env[find_path_in_env(env, "PATH=")], "PATH=");
	if (!path)
		return (NULL);
	them_paths = ft_split(path, ':');
	if (!them_paths)
		return (NULL);
	i = 0;
	while (them_paths[i])
	{
		path = ft_strjoin(them_paths[i], cmd);
		if (access(path, F_OK))
			break ;
		free(path);
		i++;
	}
	return (path);
}
char *find_env(char **env)
{
	int		i;
	char	*path;
	char	**them_paths;

	path = ft_strtrim(env[find_path_in_env(env, "PATH=")], "PATH=");
	if (!path)
		return (NULL);
	them_paths = ft_split(path, ':');
	if (!them_paths)
		return (NULL);
	i = 0;
	while (them_paths[i])
	{
		path = ft_strjoin(them_paths[i], cmd);
		if (access(path, F_OK))
			break ;
		free(path);
		i++;
	}
	return (path);
}

int	main(int argc, char **argv, char **env)
{
	t_pipex pipex;

	if (argc != 5)
		msg_error("Error, the number of arguments is incorrect");
	pipex.in_fd = open(argv[1], O_RDONLY);
	if (pipex.in_fd < 0)
		msg_error("Error infile");
	pipex.out_fd = open(argv[argc - 1], O_CREAT | O_RDWR);
	if (pipex.out_fd < 0)
		msg_error("Error outfile");
	pipex.env_path = find_env(env);
	pipex.cmd_path[0] = find_path(env, extract_cmd(argv[2]));
	if (!cmd[0])
	{
		perror("cmd path doesn't exist");
		exit(EXIT_FAILURE);
	}
	cmd[1] = extract_args(argv[2], extract_cmd(argv[2]));
	if (!cmd[1])
		cmd[1] = argv[1];
	else
		cmd[2] = argv[1];
	if (!cmd[1])
	{
		perror("args does't exist");
		exit(EXIT_FAILURE);
	}
	cmd[3] = NULL;
	pid = fork();
	if (pid == -1)
	{
		perror("fork failed");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		close(pipefd[0]);
		if (dup2(pipefd[1], STDOUT_FILENO) == -1)
		{
			perror("dup2 failed");
			exit(EXIT_FAILURE);
		}
		printf("AALO");
		if (execve(cmd[0], cmd, env) == -1)
		{
			perror("execve 1 failed");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		if (wait(NULL) == -1)
		{
			perror("wait() error :()");
			exit(EXIT_FAILURE);
		}
		close(pipefd[1]);
		pid = fork();
		if (pid == -1)
		{
			perror("fork2 failed");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			close(pipefd[1]);
			if (dup2(pipefd[0], STDIN_FILENO) == -1)
			{
				perror("dup2 failed (2eprocess)");
				exit(EXIT_FAILURE);
			}
			fd = open(argv[4], O_WRONLY | O_CREAT, 0666);
			if (fd == -1)
			{
				perror("open/create output.txt failed");
				exit(EXIT_FAILURE);
			}
			dup2(fd, STDOUT_FILENO);
			cmd[0] = find_path(env, extract_cmd(argv[3]));
			if (!cmd[0])
				exit(EXIT_FAILURE);
			cmd[1] = extract_args(argv[3], extract_cmd(argv[3]));
			cmd[2] = NULL;
			execve(cmd[0], cmd, env);
			perror("execve 2 failed");
			exit(EXIT_FAILURE);
		}
		else
		{
			if (wait(NULL) == -1)
			{
				perror("wait() error");
				exit(EXIT_FAILURE);
			}
			close(pipefd[0]);
		}
	}
	return (0);
}
