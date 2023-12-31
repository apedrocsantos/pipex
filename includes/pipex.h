/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 09:58:25 by anda-cun          #+#    #+#             */
/*   Updated: 2023/07/06 18:14:28 by anda-cun         ###   ########.fr       */
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
	char	**cmd_list;
	char	*shell;
	int		ifd;
	int		ofd;
	int		**fd;
	int		cmd_nbr;
}			t_pipe;

void		check_paths(t_pipe *pipe, int i);
void		mega_free(t_pipe pipe);
void		close_fds(t_pipe *pipex, int j);
int			init_fds(t_pipe *pipex);
int			init_pipex(char *envp[], t_pipe *pipex, int argc, char *argv[]);
char		*join_three(char *s1, char *s2, char *s3);
void		write_error(t_pipe *pipex, char *arg, int error);
void		get_shel(int argc, char *envp[], t_pipe *pipex);
int			open_io(t_pipe *pipex, int argc, char *argv[]);
int			here_doc(int fd, char *delim);
char		*join_two(char *s1, char *s2);
char		*get_next_line(int fd);
void		get_shell(int argc, char *argv[], char *envp[], t_pipe *pipex);

#endif
