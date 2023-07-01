/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 20:01:51 by anda-cun          #+#    #+#             */
/*   Updated: 2023/07/02 00:02:41 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	close_fds(t_pipe *pipex)
{
	int	i;

	i = pipex->cmd_nbr;
	while (i--)
	{
		// ft_printf("closing %d and %d\n", pipex->fd[i][0], pipex->fd[i][1]);
		if (close(pipex->fd[i][0]) == -2)
			ft_printf("error closing fd[%d][0]\n", i);
		if (close(pipex->fd[i][1]) == -2)
			ft_printf("error closing fd[%d][1]\n", i);
		if (pipex->outfile != -1)
		{
			if (close(pipex->outfile) == -2)
				ft_printf("error closing outfile %d\n", pipex->outfile);
		}
	}
}

void	write_error(t_pipe *pipex, char *arg)
{
	char	*str;
	char	*str2;
	char	*error;

	error = ft_strdup(strerror(errno));
	*error += 32;
	str = join_three(pipex->shell, ": ", error);
	str2 = join_three(str, ": ", arg);
	ft_putendl_fd(str2, 2);
	free(str);
	free(str2);
	free(error);
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
