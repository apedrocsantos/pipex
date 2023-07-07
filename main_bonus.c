/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 15:59:10 by anda-cun          #+#    #+#             */
/*   Updated: 2023/07/07 16:25:25 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/pipex.h"

void	child_process(t_pipe *pipex, int i, char *envp[])
{
	if (i == 0)
		dup2(pipex->ifd, STDIN_FILENO);
	else
		dup2(pipex->fd[i][0], STDIN_FILENO);
	if (i == pipex->cmd_nbr - 1)
		dup2(pipex->ofd, STDOUT_FILENO);
	else
		dup2(pipex->fd[i + 1][1], STDOUT_FILENO);
	if (execve(pipex->cmd_list[i], pipex->args[i], envp) == -1)
	{
		write_error(pipex, pipex->cmd_list[i], 1);
		close_fds(pipex, i);
		close(pipex->ofd);
		mega_free(*pipex);
		exit(127);
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
			break ;
		if (i == 0 && pipex->ifd == -1)
			i++;
		close(pipex->fd[i][1]);
		if (pid == 0)
			child_process(pipex, i, envp);
	}
	i = -1;
	while (++i < pipex->cmd_nbr)
		waitpid(-1, &status, 0);
	close_fds(pipex, i);
	close(pipex->ofd);
	return (WEXITSTATUS(status));
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipe	pipex;
	int		return_value;

	return_value = 0;
	if (argc < 5 || (!ft_strncmp(argv[1], "here_doc", 9) && argc < 6))
	{
		ft_putstr_fd(("Incorrect number of arguments\n"), 2);
		return (1);
	}
	get_shell(argc, argv, envp, &pipex);
	return_value = open_io(&pipex, argc, argv);
	if (return_value != 0)
		return (return_value);
	if (init_pipex(envp, &pipex, argc, argv) == -1)
	{
		ft_putstr_fd(("Error while creating pipes\n"), 2);
		return (1);
	}
	return_value = ft_pipex(&pipex, envp);
	if (return_value == -1)
		ft_putstr_fd("Error while forking. Program closed.\n", 2);
	if (!ft_strncmp(argv[1], "here_doc", 9))
		unlink("here_doc");
	mega_free(pipex);
	return (return_value);
}
