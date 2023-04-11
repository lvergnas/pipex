/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvergnas <lvergnas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 13:49:25 by lvergnas          #+#    #+#             */
/*   Updated: 2023/04/11 16:06:31 by lvergnas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>

int main(int argc, char **argv)
{
	char **cmd;
	pid_t pid;
	int status;
	int pipefd[2];
	int fd;

	if (argc != 5)
	{
		printf("Error, the number of arguments is incorrect");
		return (0);
	}
	//creation pipe
	if(pipe(pipefd) == -1)
	{
		perror("Pipe failed");
		exit(EXIT_FAILURE);
	}
	//parsing
	cmd = (char **)malloc(sizeof(char *) * (argc + 1));
	cmd[0] = ft_strjoin("/usr/bin/", argv[2]);
	cmd[1] = argv[1];
	
	pid = fork();
	//fork
	if (pid == -1)
	{
		perror("fork failed");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0) //child
	{
		close(pipefd[0]); //close read
		if(dup2(pipefd[1], STDOUT_FILENO) == -1) //output cmd1 dans pipe
		{
			perror("dup2 failed");
			exit(EXIT_FAILURE);
		}
		//pour cmd[0] TODO: séparer les arguments de la cmd et la cmd
		if (execve(cmd[0], cmd, NULL) == -1) {
			perror("execve 1 failed");
			exit(EXIT_FAILURE);
		}
	}
	else //parent
	{
		close(pipefd[1]); //close write
		if (wait(&status) == -1) 
		{
			perror("wait failed");
			exit(EXIT_FAILURE);
		}
		printf("\n CHILD1 done");

		pid = fork(); //2e process
		if (pid == -1)
		{
			perror("fork2 failed");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0) //child
		{
			close(pipefd[1]); // close write
			if (dup2(pipefd[0], STDIN_FILENO) ==  -1)
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
			cmd[0] = ft_strjoin("/usr/bin/", argv[3]);
			cmd[1] = argv[4];
			//pour cmd[0] séparer les arguments de la cmd et la cmd
			if (execve(cmd[0], cmd, NULL) == -1) {
				perror("execve 2 failed");
				exit(EXIT_FAILURE);
			}
		}
		else //parent
		{
			close(pipefd[0]); //close read
			if (wait(&status) == -1) 
			{
				perror("wait failed");
				exit(EXIT_FAILURE);
			}
			printf("\n CHILD2 done \nFIN");
		}
	}

	return (0);
}