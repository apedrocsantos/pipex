/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 09:58:25 by anda-cun          #+#    #+#             */
/*   Updated: 2023/06/23 13:08:26 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

typedef struct p_list {
    char ***commands;
    char **path_list;
    char *path;
    
}   pipe_list;

char    *check_path(char **paths, char *commands);
void    mega_free(pipe_list pipe);