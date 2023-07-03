/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 15:59:10 by anda-cun          #+#    #+#             */
/*   Updated: 2023/07/04 00:14:31 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
TODO: errors, check fds, make heredoc
*/

#include "./includes/pipex.h"

void	child_process(t_pipe *pipex, int i, char *envp[])
{
	if (i == 0)
		dup2(pipex->infile, STDIN_FILENO);
	else
		dup2(pipex->fd[i][0], STDIN_FILENO);
	if (i == pipex->cmd_nbr - 1)
		dup2(pipex->outfile, STDOUT_FILENO);
	else
		dup2(pipex->fd[i + 1][1], STDOUT_FILENO);
	if (execve(pipex->cmd_list[i], pipex->args[i], envp) == -1)
	{
		write_error(pipex, pipex->cmd_list[i]);
		if (pipex->infile != -1)
			close(pipex->infile);
		close(pipex->outfile);
		close_fds(pipex, i);
		exit (-1);
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
		if (pid == -1)
		{
			ft_putstr_fd("Error while forking. Closing.\n", 2);
			if (pipex->infile != -1)
				close(pipex->infile);
			close_fds(pipex, i);
			close(pipex->outfile);
			return (-1);
		}
		if (i == 0 && pipex->infile == -1)
			i++;
		close(pipex->fd[i][1]);
		if (pid == 0)
			child_process(pipex, i, envp);
		wait(&status);
	}
	if (pipex->infile != -1)
		close(pipex->infile);
	close_fds(pipex, i);
	close(pipex->outfile);
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
		return (-1);
	}
	if (init_pipex(envp, &pipex, argc, argv) == -1)
		return (-1);
	if (open_io(&pipex, argc, argv) == -1)
		return (EPERM);
	return_value = ft_pipex(&pipex, envp);
	if (return_value == -1)
		ft_putstr_fd("Error while forking. Program closed.\n", 2);
	mega_free(pipex);
	return (return_value);
}
