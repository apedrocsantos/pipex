/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 20:01:51 by anda-cun          #+#    #+#             */
/*   Updated: 2023/07/06 17:53:09 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	get_shell(int argc, char *argv[], char *envp[], t_pipe *pipex)
{
	int	i;

	i = -1;
	while (envp[++i])
	{
		if (ft_strnstr(envp[i], "SHELL=", 6))
		{
			pipex->shell = ft_strrchr(envp[i], '/');
			pipex->shell++;
		}
	}
	if (!ft_strncmp(argv[1], "here_doc", 9))
		pipex->cmd_nbr = argc - 4;
	else
		pipex->cmd_nbr = argc - 3;
}

void	close_fds(t_pipe *pipex, int j)
{
	int	i;

	i = pipex->cmd_nbr;
	if (pipex->ifd != -1)
		close(pipex->ifd);
	while (i--)
	{
		close(pipex->fd[i][0]);
		if (i > j)
			close(pipex->fd[i][1]);
	}
}

void	write_error(t_pipe *pipex, char *arg, int is_command)
{
	char	*str;
	char	*str2;
	char	*error_msg;

	error_msg = ft_strdup(strerror(errno));
	*error_msg += 32;
	if (is_command && !ft_strchr(arg, '/'))
	{
		free(error_msg);
		error_msg = ft_strdup("command not found");
	}
	str = join_three(pipex->shell, ": ", error_msg);
	str2 = join_three(str, ": ", arg);
	ft_putendl_fd(str2, STDERR_FILENO);
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
