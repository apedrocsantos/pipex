/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 09:55:29 by anda-cun          #+#    #+#             */
/*   Updated: 2023/07/02 10:51:13 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

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

int	check_paths(t_pipe *pipex, int j)
{
	int		i;
	char	*str_to_check;

	i = 0;
	while (pipex->path_list[i])
	{
		str_to_check = join_three(pipex->path_list[i], "/", *pipex->args[j]);
		if (access(str_to_check, X_OK) == 0)
		{
			free(*pipex->args[j]);
			*pipex->args[j++] = str_to_check;
			break ;
		}
		if (!pipex->path_list[i + 1])
		{
			free(str_to_check);
			break ;
		}
		i++;
		free(str_to_check);
	}
	return (0);
}

void	init_pipex(char *envp[], t_pipe *pipex, int argc, char *argv[])
{
	int	i;

	pipex->cmd_nbr = argc - 3;
	while (envp[++i])
	{
		if (ft_strnstr(envp[i], "PATH=", 5))
			pipex->path_list = ft_split(&envp[i][5], ':');
		if (ft_strnstr(envp[i], "SHELL=", 6))
		{
			pipex->shell = ft_strrchr(envp[i], '/');
			pipex->shell++;
		}
	}
	pipex->args = (char ***)ft_calloc(argc - 2, sizeof(char ***));
	i = -1;
	while ((++i + 2) < argc - 1)
	{
		pipex->args[i] = split_args(argv[i + 2]);
		// int j = -1;
		// while (pipex->args[i][++j])
		// 	ft_printf("%s\n", pipex->args[i][j]);
		if (!ft_strchr(*pipex->args[i], '/'))
			check_paths(pipex, i);
	}
	i = -1;
	init_fds(pipex);
}
