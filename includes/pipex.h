/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 09:58:25 by anda-cun          #+#    #+#             */
/*   Updated: 2023/06/25 16:52:09 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>
# include "errno.h"

typedef struct a_list
{
	char	***args;
	char	**path_list;
	char	*shell;

}			t_pipe;

int	check_path(char **paths, t_pipe *pipe);
void	mega_free(t_pipe pipe);

# endif
