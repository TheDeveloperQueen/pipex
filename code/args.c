/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args&cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rivasque <rivasque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 12:33:55 by rivasque          #+#    #+#             */
/*   Updated: 2023/12/18 13:18:41 by rivasque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char **ft_path(char *env)
{
	
}

char	**ft_args(char *args)
{
	char	**array_args;
	
	array_args = ft_split(args, ' ');
	return (array_args);
}

char **ft_cmds(char *cmds)
{
	char	**array_cmds;
	int	i;

	while (cmds[i] != '/')
		i++;
	array_cmds = ft_split(cmds, ':');
}