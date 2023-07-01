/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 20:01:51 by anda-cun          #+#    #+#             */
/*   Updated: 2023/07/01 20:35:19 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	close_fds(int i, t_pipe *pipex)
{
	i = pipex->cmd_nbr;
	while (i--)
	{
		// ft_printf("closing %d and %d\n", pipex->fd[i][0], pipex->fd[i][1]);
		if (close(pipex->fd[i][0]) == -2)
			ft_printf("error closing fd[%d][0]\n", i);
		if (close(pipex->fd[i][1]) == -2)
			ft_printf("error closing fd[%d][1]\n", i);
		if (close(pipex->outfile) == -2)
			ft_printf("error closing outfile %d\n", pipex->outfile);
	}
}

void	init_fds(t_pipe *pipex)
{
	int	i;

	pipex->fd = (int **)calloc((pipex->cmd_nbr + 1), sizeof(int **));
	i = -1;
	while (++i < pipex->cmd_nbr)
		pipex->fd[i] = (int *)malloc(sizeof(int *) * 2);
	i = -1;
	while (++i < pipex->cmd_nbr)
		pipe(pipex->fd[i]);
}

void	init_pipex(char *envp[], t_pipe *pipex, int argc, char *argv[])
{
	int	i;
	int	j;

	i = -1;
	pipex->cmd_nbr = argc - 3;
	pipex->args = (char ***)malloc(sizeof(char ***) * (argc - 2));
	while (envp[++i])
	{
		if (ft_strnstr(envp[i], "PATH=", sizeof((envp[i]))))
			pipex->path_list = ft_split(&envp[i][5], ':');
		if (ft_strnstr(envp[i], "SHELL=", sizeof((envp[i]))))
		{
			pipex->shell = ft_strrchr(envp[i], '/');
			pipex->shell++;
		}
	}
	j = -1;
	while ((++j + 2) < argc - 1)
		pipex->args[j] = ft_split(argv[j + 2], ' ');
	pipex->args[j] = NULL;
	init_fds(pipex);
}

void	write_error(t_pipe *pipex, char *arg)
{
	char	*str;
	char	*str2;

	str = join_three(pipex->shell, ": ", strerror(errno));
	str2 = join_three(str, ": ", arg);
	ft_putendl_fd(str2, 2);
	free(str);
	free(str2);
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
