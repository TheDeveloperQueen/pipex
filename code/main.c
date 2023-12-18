/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rivasque <rivasque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 09:55:52 by rivasque          #+#    #+#             */
/*   Updated: 2023/12/18 13:20:48 by rivasque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **env)
{
	char *argument[] = {
		"cat",
		"infile",
		NULL
	};
	
	("/bin/cat", argument, env);

	char *argument2[] = {
		"cat",
		"infile2",
		NULL
	};

	execve("/bin/cat", argument2, env);
}