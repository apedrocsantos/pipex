/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 15:59:10 by anda-cun          #+#    #+#             */
/*   Updated: 2023/06/29 19:01:57 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/pipex.h"

void	get_paths(char *envp[], t_pipe *pipex, int argc, char *argv[])
{
	int	i;
	int	j;

	i = -1;
	pipex->path = (char **)malloc(sizeof(char **) * (argc - 2));
	pipex->args = (char ***)malloc(sizeof(char ***) * (argc - 2));
	pipex->args[argc - 3] = NULL;
	pipex->path[argc - 3] = NULL;
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
}

int	ft_pipex(char *argv[], t_pipe *pipex, int argc)
{
	int	i;
	int	status;
	int	fd[argc - 2][2];
	int	pid[argc - 3];
	int temp;

	status = 0;
	i = 0;
	while (i <= argc - 3)
		pipe(fd[i++]);
	temp = open(argv[1], O_RDONLY);
	if (temp != -1)
		fd[0][0] = temp;
	close(fd[0][1]);
	close(fd[argc - 3][0]);
	temp = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 00664);
	if (temp != -1)
		fd[argc - 3][1] = temp;
	else
		return (ft_printf("%s: %s: %s\n", pipex->shell, strerror(EACCES), argv[argc - 1]));
	i = 0;
	while (i < argc - 3)
	{
		pid[i] = fork();
		if (pid[i] == 0)
		{
			dup2(fd[i][0], STDIN_FILENO);
			close(fd[i][0]);
			dup2(fd[i + 1][1], STDOUT_FILENO);
			close(fd[i + 1][1]);
			if (execve(pipex->path[i], pipex->args[i], NULL) == -1)
			{
				mega_free(*pipex);
				exit(-1);
			}
		}
		wait(&status);
		close(fd[i][0]);
		close(fd[i + 1][1]);
		i++;
	}
	if (status)
		return (-1);
	return (0);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipe	pipex;
	int fd;

	if (argc < 5)
	{
		ft_printf("Incorrect number of arguments\n");
		return (1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		ft_printf("%s: %s: %s\n", "zsh", strerror(errno), argv[1]);
		close(fd);
	}
	get_paths(envp, &pipex, argc, argv);
	if (check_path(pipex.path_list, &pipex) == -1)
		return (0);
	if (ft_pipex(argv, &pipex, argc) == -1)
	{
		mega_free(pipex);
		return (127);
	}
	mega_free(pipex);
	return (0);
}
