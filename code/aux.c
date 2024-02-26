/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rivasque <rivasque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 11:10:55 by rivasque          #+#    #+#             */
/*   Updated: 2024/02/26 14:57:12 by rivasque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	open_file(char *file, int mode)
{
	int	fd;

	if (mode == 0)
		fd = open(file, O_RDONLY);
	if (mode == 1)
		fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror(NULL);
		exit(EXIT_FAILURE);
	}
	return (fd);
}

static void	child_process1(int	*files, char **argv, char **env)
{
	char	*path;
	char	**comds;
	int		infile;
	
	infile = open_file(argv[1], 0);
	close(files[0]);
	comds = cmds(argv[2]);
	path = paths(env, comds[0]);
	dup2(infile, STDIN_FILENO);
	close(infile);
	dup2(files[1], STDOUT_FILENO);
	close(files[1]);
	execve(path, comds, env);
	perror(comds[0]);
	exit(EXIT_FAILURE);
}

static void	child_process2(int *files, char **argv, char **env)
{
	char	*path;
	char	**comds;
	int		outfile;

	outfile = open_file(argv[4], 1);
	close(files[1]);
	comds = cmds(argv[3]);
	path = paths(env, comds[0]);
	dup2(outfile, STDOUT_FILENO);
	close(outfile);
	dup2(files[0], STDIN_FILENO);
	close(files[0]);
	execve(path, comds, env);
	perror(comds[0]);
	exit(EXIT_FAILURE);
}

void	pipex(char **argv, char **env)
{
	int		files[2];
	pid_t	child1;
	pid_t	child2;
	int		status;

	pipe(files);
	child1 = fork();
	if (child1 < 0)
		exit(EXIT_FAILURE);
	if (child1 == 0)
		child_process1(files, argv, env);
	child2 = fork();
	if (child2 < 0)
		exit(EXIT_FAILURE);
	if (child2 == 0)
		child_process2(files, argv, env);
	close(files[0]);
	close(files[1]);
	waitpid(child1, NULL, 0);
	waitpid(child2, &status, 0);
	exit(WEXITSTATUS(status));
}
