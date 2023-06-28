/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 15:59:10 by anda-cun          #+#    #+#             */
/*   Updated: 2023/06/28 20:56:18 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/pipex.h"

void	get_paths(char *envp[], t_pipe *pipe)
{
	int	i;

	i = -1;
	while (envp[++i])
	{
		if (ft_strnstr(envp[i], "PATH=", sizeof((envp[i]))))
			pipe->path_list = ft_split(&envp[i][5], ':');
		if (ft_strnstr(envp[i], "SHELL=", sizeof((envp[i]))))
		{
			pipe->shell = ft_strrchr(envp[i], '/');
			pipe->shell++;
		}
	}
}

int	ft_pipex(char *argv[], t_pipe *pipex, int argc)
{
	int	i;
	int	fd[argc - 2][2];
	int	pid[argc - 3];

	i = 0;
	while (i < argc - 2)
		pipe(fd[i++]);
	fd[0][0] = open(argv[1], O_RDONLY);
	if (fd[0][0] == -1)
		return (-1);
	close(fd[0][1]);
	close(fd[argc - 3][0]);
	fd[argc - 3][1] = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 00664);
	i = 0;
	while (i < argc - 3)
	{
		pid[i] = fork();
		if (pid[i] == 0)
		{
			dup2(fd[i][0], STDIN_FILENO);
			dup2(fd[i + 1][1], STDOUT_FILENO);
			if (execve(pipex->path[i], pipex->args[i], NULL) == -1)
				return(-1);
		}
		waitpid(pid[i], NULL, 0);
		close(fd[i][0]);
		close(fd[i + 1][1]);
		i++;
	}
	return (0);
}

int	main(int argc, char *argv[], char *envp[])
{
	int i;
	int j;
	t_pipe pipex;
	if (argc >= 5)
	{
		get_paths(envp, &pipex);
		pipex.path = (char **)malloc(sizeof(char **) * (argc - 2));
		*pipex.path = NULL;
		pipex.args = (char ***)malloc(sizeof(char ***) * (argc - 2));
		i = 2;
		j = 0;
		while (i < argc - 1)
			pipex.args[j++] = ft_split(argv[i++], ' ');
		pipex.args[j] = NULL;
		if (check_path(pipex.path_list, &pipex) == -1)
			return (0);
		i = 0;
		if (ft_pipex(argv, &pipex, argc) == -1)
		{
			mega_free(pipex);
			return (127);
		}
		mega_free(pipex);
		return(0);
	}
	return (2);
}