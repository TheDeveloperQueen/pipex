/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rivasque <rivasque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 10:54:34 by rivasque          #+#    #+#             */
/*   Updated: 2024/02/29 11:16:38 by rivasque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>

char	**cmds_b(char *argv);
char	*paths_b(char **env, char *cmd);
void	pipex_b(int argc, char **argv, char **env);
int		n_cmds(int argc, char **argv);
void	ft_wait(pid_t child_last);
char	*here_doc(char *delimiter);

#endif