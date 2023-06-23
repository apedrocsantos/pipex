/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mega_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 11:20:49 by anda-cun          #+#    #+#             */
/*   Updated: 2023/06/23 13:12:18 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void    mega_free(pipe_list pipe)
{
    int i = 0;
    int j = 0;

    while (pipe.commands[i])
    {
        while (pipe.commands[i][j])
            free(pipe.commands[i][j++]);
        free(pipe.commands[i]);
        j = 0;
        i++;
    }
    free(pipe.commands);
    i = 0;
    while (pipe.path_list[i])
        free(pipe.path_list[i++]);
    free(pipe.path_list[i]);
    free(pipe.path_list);
    free(pipe.path);
}