/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 09:58:25 by anda-cun          #+#    #+#             */
/*   Updated: 2023/07/01 23:25:19 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "errno.h"
# include "libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct a_list
{
	char	***args;
	char	**path_list;
	char	*shell;
	int		infile;
	int		outfile;
	int		**fd;
	int		cmd_nbr;
}			t_pipe;

int			check_paths(t_pipe *pipe, int i);
void		mega_free(t_pipe pipe);
void		close_fds(t_pipe *pipex);
void		init_fds(t_pipe *pipex);
void		init_pipex(char *envp[], t_pipe *pipex, int argc, char *argv[]);
char		*join_three(char *s1, char *s2, char *s3);
void		write_error(t_pipe *pipex, char *arg);

#endif
