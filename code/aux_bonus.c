/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rivasque <rivasque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 10:56:23 by rivasque          #+#    #+#             */
/*   Updated: 2024/02/28 15:40:56 by rivasque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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


//NOT TAKING INTO ACCOUT HERE_DOC (cmds_b(ARGV[2]))
static int	child_process_1st(char **argv, char **env)
{
	char	*path;
	char	**comds;
	int		infile;
	int		use_pipe[2];
	pid_t	child;
	
	comds = cmds_b(argv[2]);
	path = paths_b(env, comds[0]);
	pipe(use_pipe);
	child = fork();
	if (child < 0)
		exit(EXIT_FAILURE);
	if (child == 0)
	{
		infile = open_file(argv[1], 0);
		dup2(infile, STDIN_FILENO);
		close(infile);
		dup2(use_pipe[1], STDOUT_FILENO);
		close(use_pipe[1]);
		execve(path, comds, env);
		perror(comds[0]);
		exit(EXIT_FAILURE);
	}
	return(close(use_pipe[1]), use_pipe[0]);
}

static int	child_process_middle(int pipe_a, char **argv, char **env)
{
	char	*path;
	char	**comds;
	int		use_pipe[2];
	pid_t	child;
		
	comds = cmds_b(*argv);
	path = paths_b(env, comds[0]);
	pipe(use_pipe);
	child = fork();
	if (child < 0)
		exit(EXIT_FAILURE);
	if (child == 0)
	{
		dup2(pipe_a, STDIN_FILENO);
		close(pipe_a);
		dup2(use_pipe[1], STDOUT_FILENO);
		close(use_pipe[1]);
		execve(path, comds, env);
		perror(comds[0]);
		exit(EXIT_FAILURE);
	}
	close(use_pipe[1]);
	close(pipe_a);
	return(use_pipe[0]);
}

static pid_t	child_process_last(int argc, int pipe_a, char **argv, char **env)
{
	char	*path;
	char	**comds;
	int		outfile;
	pid_t	child_last;

	outfile = open_file(argv[argc - 1], 1);
	comds = cmds_b(argv[argc - 2]);
	path = paths_b(env, comds[0]);
	child_last = fork();
	if (child_last < 0)
		exit(EXIT_FAILURE);
	if (child_last == 0)
	{
		dup2(outfile, STDOUT_FILENO);
		close(outfile);
		dup2(pipe_a, STDIN_FILENO);
		close(pipe_a);
		execve(path, comds, env);
		perror(comds[0]);
		exit(EXIT_FAILURE);
	}
	return (child_last);
}
//NOT TAKING INTO ACCOUT HERE_DOC (i = 3)
void	pipex_b(int argc, char **argv, char **env)
{
	int		i;
	int		n_comds;
	int		pipe_a;
	pid_t	last_child;
	
	i = 3;
	if ((ft_strncmp(argv[1], "here_doc", 8) == 0) && ft_strlen(argv[1]) == 8)
	{
		argv++;
		argv[1] = here_doc(argv[1]);
	}
	n_comds = n_cmds(argc, argv);
	pipe_a = child_process_1st(argv, env);
	while (i <= n_comds)
	{
		pipe_a = child_process_middle(pipe_a, &argv[i], env);
		i++;
	}
	last_child = child_process_last(argc, pipe_a, argv, env);
	ft_wait(last_child);
}
