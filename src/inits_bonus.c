/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 09:55:29 by anda-cun          #+#    #+#             */
/*   Updated: 2023/07/06 17:55:13 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	open_io(t_pipe *pipex, int argc, char *argv[])
{
	if (!strncmp(argv[1], "here_doc", 9))
		pipex->ofd = open(argv[argc - 1], O_CREAT | O_WRONLY | O_APPEND, 0664);
	else
		pipex->ofd = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0664);
	if (pipex->ofd == -1)
	{
		write_error(pipex, argv[argc - 1], 0);
		return (1);
	}
	if (!strncmp(argv[1], "here_doc", 9))
	{
		pipex->ifd = open(argv[1], O_CREAT | O_WRONLY | O_EXCL | O_APPEND,
				0664);
		if (pipex->ifd == -1)
		{
			perror("here_doc");
			return (1);
		}
		here_doc(pipex->ifd, argv[2]);
	}
	pipex->ifd = open(argv[1], O_RDONLY);
	if (pipex->ifd == -1)
		write_error(pipex, argv[1], 0);
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
	int	g;

	i = -1;
	while (envp[++i])
	{
		if (ft_strnstr(envp[i], "PATH=", 5))
			pipex->path_list = ft_split(&envp[i][5], ':');
	}
	pipex->args = (char ***)ft_calloc(pipex->cmd_nbr + 1, sizeof(char ***));
	pipex->cmd_list = (char **)ft_calloc(pipex->cmd_nbr + 1, sizeof(char **));
	i = -1;
	g = 2;
	if (!ft_strncmp(argv[1], "here_doc", 9))
		g++;
	while (g < argc - 1)
	{
		pipex->args[++i] = ft_split(argv[g++], ' ');
		pipex->cmd_list[i] = ft_strdup(pipex->args[i][0]);
		if (!ft_strchr(pipex->cmd_list[i], '/'))
			check_paths(pipex, i);
	}
	return (init_fds(pipex));
}
