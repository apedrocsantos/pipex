/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 20:01:51 by anda-cun          #+#    #+#             */
/*   Updated: 2023/07/05 12:13:50 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	close_fds(t_pipe *pipex, int j)
{
	int	i;

	i = pipex->cmd_nbr;
	if (pipex->infile != -1)
		close(pipex->infile);
	while (i--)
	{
		close(pipex->fd[i][0]);
		if (i > j)
			close(pipex->fd[i][1]);
	}
}

void	write_error(t_pipe *pipex, char *arg, int error)
{
	char	*str;
	char	*str2;
	char	*error_msg;

	error_msg = ft_strdup(strerror(errno));
	*error_msg += 32;
	if (error && !ft_strchr(arg, '/'))
	{
		free(error_msg);
		error_msg = ft_strdup("command not found");
	}
	str = join_three(pipex->shell, ": ", error_msg);
	str2 = join_three(str, ": ", arg);
	ft_putendl_fd(str2, 2);
	free(str);
	free(str2);
	free(error_msg);
}

char	*join_three(char *s1, char *s2, char *s3)
{
	char	*one;
	char	*two;

	one = ft_strjoin(s1, s2);
	two = ft_strjoin(one, s3);
	free(one);
	return (two);
}
