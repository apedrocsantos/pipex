/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 15:59:10 by anda-cun          #+#    #+#             */
/*   Updated: 2023/07/02 11:02:26 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
TODO: create list of paths, check errors, check fds, make heredoc
*/

#include "./includes/pipex.h"

void	child_process(t_pipe *pipex, int i, char *envp[])
{
	if (i == 0)
	{
		if (pipex->infile == -1)
		{
			close_fds(pipex);
			mega_free(*pipex);
			exit(-1);
		}
		dup2(pipex->infile, STDIN_FILENO);
	}
	else
		dup2(pipex->fd[i][0], STDIN_FILENO);
	if (i == pipex->cmd_nbr - 1)
		dup2(pipex->outfile, STDOUT_FILENO);
	else
		dup2(pipex->fd[i + 1][1], STDOUT_FILENO);
	if (execve(pipex->args[i][0], pipex->args[i], envp) == -1)
	{
		write_error(pipex, pipex->args[i][0]);
		if (pipex->infile != -1)
			close(pipex->infile);
		close_fds(pipex);
		mega_free(*pipex);
		exit(-1);
	}
}

int	ft_pipex(t_pipe *pipex, char *envp[])
{
	int	i;
	int	pid;
	int	status;

	i = -1;
	while (++i < pipex->cmd_nbr)
	{
		pid = fork();
		close(pipex->fd[i][1]);
		if (pid == 0)
			child_process(pipex, i, envp);
		if (pipex->infile == -1)
			close(pipex->fd[0][0]);
		wait(&status);
	}
	close_fds(pipex);
	close(pipex->infile);
	if (status)
		return (-1);
	return (0);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipe	pipex;
	int		return_value;

	return_value = 0;
	if (argc < 5)
	{
		ft_putstr_fd(("Incorrect number of arguments\n"), 2);
		return (1);
	}
	init_pipex(envp, &pipex, argc, argv);
	pipex.infile = open(argv[1], O_RDONLY);
	if (pipex.infile == -1)
		write_error(&pipex, argv[1]);
	pipex.outfile = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 00664);
	if (pipex.outfile == -1)
	{
		if (pipex.infile != -1)
			close(pipex.infile);
		close_fds(&pipex);
		mega_free(pipex);
		write_error(&pipex, argv[argc - 1]);
		return (1);
	}
	split_args("aeiouo 'asdlfkj  asd'    b   ");
	if (ft_pipex(&pipex, envp) == -1)
		return_value = 1;
	mega_free(pipex);
	return (return_value);
}
