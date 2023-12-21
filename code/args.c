/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rivasque <rivasque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 12:33:55 by rivasque          #+#    #+#             */
/*   Updated: 2023/12/21 15:14:26 by rivasque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char **find_path(char **env)
{
	int 	i;
	char	**paths;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	if (env[i] == NULL)
		return NULL;
	paths = ft_split(env[i] + 5, ':');
	if (!paths)
		return NULL;
	return (paths);
}

char	**cmds(char *argv)
{
	char	**array_cmds;
	
	array_cmds = ft_split(argv, ' ');
	return (array_cmds);
}
// cmd = al cmds[0]
char *paths(char **env, char *cmd)
{
	char	**array_paths;
	char 	*full_path;
	int	i;

	i = 0;
	if (cmd[0] == '/' || ft_strncmp(cmd, "../", 3) == 0
	 || ft_strncmp(cmd, "./", 2) == 0)
	 	return (cmd);
	array_paths = find_path(env);
	while (array_paths[i] != NULL)
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
	return NULL;
}
