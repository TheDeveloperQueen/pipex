/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rivasque <rivasque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 19:30:46 by ritavasques       #+#    #+#             */
/*   Updated: 2024/02/28 15:49:40 by rivasque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

// Check if here_doc ok
int input_here_doc(int fd, char *delimiter)
{
    char    *data;
    char    *del_newline;
    
    del_newline = ft_strjoin(delimiter, "\n");
    if (!del_newline)
        return (0);
    data = get_next_line(0);
    while (data && ft_strcmp(data, del_newline))
    {
        write (fd, data, ft_strlen(data));
        free(data);
        data = get_next_line(0);
    }
    if (data)
        free(data);
    free(del_newline);
    return (1);
}

char    *here_doc(char *delimiter)
{
    int     fd;
    char    *path;
    int     file_ok;

    if (!delimiter)
        return (NULL);
    path = ft_calloc(14, sizeof(char));
    if (!path)
        return (NULL);
    ft_strcpy(path, "./here_doc.log");
    fd = open(path, O_WRONLY | O_CREAT, 0644);
    if (fd < 0)
    {
        free(path);
        return (NULL);
    }
    file_ok = input_here_doc(fd, delimiter);
    close(fd);
    if (!file_ok)
        return (NULL);
    return (path);
}
