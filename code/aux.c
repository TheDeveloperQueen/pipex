/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rivasque <rivasque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 11:10:55 by rivasque          #+#    #+#             */
/*   Updated: 2023/12/18 13:17:51 by rivasque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process1(int fd, char *cmd)
{
	int	files[2];
	char *path;
	char **args; 
	char *env;
	
	dup2(fd, STDIN_FILENO);
	dup2(files[1], STDOUT_FILENO);
	close(files[0]);
	close(fd);
	execve(path, args[2], env);
}

void	child_process2(int fd, char *cmd)
{
	int	files[2];
	char *path;
	char **args; 
	char *env;
	
	dup2(fd, STDOUT_FILENO);
	dup2(files[0], STDIN_FILENO);
	close(files[1]);
	close(fd);
	execve(path, args[3], env);
}

void	pipex(int fd1, int fd2)
{
	int		files[2];
	pid_t	pid[2];
	char cmd1;
	char cmd2;
	
	pipe(files);
	pid[0] = fork();
	if (pid[0] < 0)
	{
		return (1);
		exit(EXIT_FAILURE);
	}
	if (pid[0] == 0)
		child_process1(fd1, cmd1);
	pid[1] = fork();
	if (pid[1] < 0)
	{
		return (1);
		exit(EXIT_FAILURE);
	}
	if (pid[1] == 0)
		child_process2(fd2, cmd2);
	//wait();
}
