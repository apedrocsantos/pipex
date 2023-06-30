/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 09:58:25 by anda-cun          #+#    #+#             */
/*   Updated: 2023/06/30 13:43:51 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "errno.h"

typedef struct a_list
{
	char	***args;
	char	**path_list;
	char	*shell;
	// int		**fd;
	// int		*pid;

}			t_pipe;

int		check_paths(t_pipe *pipe);
void	mega_free(t_pipe pipe);

#endif
