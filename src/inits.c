/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 09:55:29 by anda-cun          #+#    #+#             */
/*   Updated: 2023/07/03 19:06:42 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	open_io(t_pipe *pipex, int argc, char *argv[])
{
	pipex->infile = open(argv[1], O_RDONLY);
	if (pipex->infile == -1)
		write_error(pipex, argv[1]);
	pipex->outfile = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 00664);
	if (pipex->outfile == -1)
	{
		if (pipex->infile != -1)
			close(pipex->infile);
		close_fds(pipex, -1);
		mega_free(*pipex);
		write_error(pipex, argv[argc - 1]);
		return (-1);
	}
	return (0);
}

int	init_fds(t_pipe *pipex)
{
	int	i;
	int	pip;

	pipex->fd = (int **)ft_calloc((pipex->cmd_nbr + 1), sizeof(int **));
	i = -1;
	while (++i < pipex->cmd_nbr)
		pipex->fd[i] = (int *)ft_calloc(2, sizeof(int *));
	i = -1;
	while (++i < pipex->cmd_nbr)
	{
		pip = pipe(pipex->fd[i]);
		if (pip == -1)
		{
			perror("Error");
			return (-1);
		}
	}
	return (0);
}

void	check_paths(t_pipe *pipex, int j)
{
	int		i;
	char	*str_to_check;

	i = 0;
	while (pipex->path_list[i])
	{
		str_to_check = join_three(pipex->path_list[i], "/", pipex->cmd_list[j]);
		if (access(str_to_check, X_OK) == 0)
		{
			free(pipex->cmd_list[j]);
			pipex->cmd_list[j++] = str_to_check;
			break ;
		}
		i++;
		free(str_to_check);
	}
}

int	init_pipex(char *envp[], t_pipe *pipex, int argc, char *argv[])
{
	int	i;

	i = 0;
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
	pipex->cmd_list = (char **)ft_calloc(argc - 2, sizeof(char **));
	i = -1;
	while ((++i + 2) < argc - 1)
	{
		pipex->args[i] = split_args(argv[i + 2]);
		pipex->cmd_list[i] = ft_strdup(pipex->args[i][0]);
		if (!ft_strchr(pipex->cmd_list[i], '/'))
			check_paths(pipex, i);
	}
	return (init_fds(pipex));
}