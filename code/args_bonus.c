/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ritavasques <ritavasques@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:45:50 by rivasque          #+#    #+#             */
/*   Updated: 2024/02/28 17:24:58 by ritavasques      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static char	**find_path(char **env)
{
	int		i;
	char	**paths;

	i = 0;
	if (!*env)
		perror("error");
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	if (env[i] == NULL)
		return (NULL);
	paths = ft_split(env[i] + 5, ':');
	if (!paths)
		return (NULL);
	return (paths);
}

char	**cmds_b(char *argv)
{
	char	**array_cmds;

	array_cmds = ft_split(argv, ' ');
	return (array_cmds);
}

int	n_cmds(int argc, char **argv)
{
	if ((ft_strncmp(argv[1], "here_doc", 8) == 0) && ft_strlen(argv[1]) == 8)
		return (argc - 4);
	else
		return (argc - 3);
}

char	*paths_b(char **env, char *cmd)
{
	char	**array_paths;
	char	*full_path;
	int		i;

	i = 0;
	if (ft_strchr(cmd, '/'))
		return (cmd);
	array_paths = find_path(env);
	while (array_paths && array_paths[i] != NULL)
	{
		full_path = ft_strjoin(array_paths[i], "/");
		full_path = ft_strjoin(full_path, cmd);
		if (access(full_path, F_OK) == 0)
		{
			free(array_paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(": command not found", 2);
	return (NULL);
}

void	ft_wait(pid_t child_last)
{
	int	last_exc;
	int	status;
	int	exit_code;

	last_exc = 0;
	while (last_exc != -1)
	{
		last_exc = waitpid(-1, &status, 0);
		if (last_exc == child_last)
			if (WIFEXITED(status))
				exit_code = WEXITSTATUS(status);
	}
	exit(exit_code);
}
