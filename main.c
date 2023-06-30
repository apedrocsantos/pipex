/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 15:59:10 by anda-cun          #+#    #+#             */
/*   Updated: 2023/06/30 17:50:47 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/pipex.h"

void	init_pipex(char *envp[], t_pipe *pipex, int argc, char *argv[])
{
	int	i;
	int	j;

	i = -1;
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
}

// int	execute(int i, t_pipe *pipex)
// {
// 	int status;
	
// 	pipex->pid[i] = fork();
// 	if (pipex->pid[i] == 0)
// 	{
// 		dup2(pipex->fd[i][0], STDIN_FILENO);
// 		close(pipex->fd[i][0]);
// 		dup2(pipex->fd[i + 1][1], STDOUT_FILENO);
// 		close(pipex->fd[i + 1][1]);
// 		if (execve(pipex->args[i][0], pipex->args[i], NULL) == -1)
// 		{
// 			mega_free(*pipex);
// 			exit(-1);
// 		}
// 	}
// 	wait(&status);
// 	close(pipex->fd[i][0]);
// 	close(pipex->fd[i + 1][1]);
// 	return(status);
// }

int	ft_pipex(char *argv[], t_pipe *pipex, int argc)
{
	int	i;
	int	status;
	int	temp;
	int fd[argc - 2][2];
	int pid[argc - 3];

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
			if (execve(pipex->args[i][0], pipex->args[i], NULL) == -1)
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

// int	ft_pipex(int argc, t_pipe *pipex, int infile)
// {
// 	int i;
// 	int fd[2];
// 	int pid;
	
// 	i = 0;
// 	pipe(fd);
// 	infile++;
// 	while (i < argc - 3)
// 	{
// 		pid = fork();
// 		if (pid == 0)
// 		{
// 			if (i == 0 && infile != -1)
// 				fd[0] = infile;
// 			else
// 			{
// 				dup2(fd[0], STDIN_FILENO);
// 				close(fd[0]);
// 			}
// 			dup2(fd[1], STDOUT_FILENO);
// 			close(fd[1]);
// 			if (execve(pipex->args[i][0], pipex->args[i], NULL) == -1)
// 				exit (-1);
// 		}
// 		wait(NULL);
// 		close(fd[1]);
// 		ft_printf("hi from dad\n");
// 		i++;
// 	}
// 	return (0);
// }

int	main(int argc, char *argv[], char *envp[])
{
	t_pipe	pipex;
	int		return_value;
	int		infile;
	int		outfile;

	return_value = 0;
	if (argc < 5)
	{
		ft_putstr_fd(("Incorrect number of arguments\n"), 2);
		return (1);
	}
	infile = open(argv[1], O_RDONLY);
	if (infile == -1)
		ft_printf("%s: no such file or directory: %s\n", "zsh", argv[1]);
	init_pipex(envp, &pipex, argc, argv);
	outfile = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 00664);
	if (outfile == -1)
	{	
		mega_free(pipex);
		ft_printf("%s: permission denied: %s\n", "zsh", argv[argc -1]);
		return (1);
	}
	check_paths(&pipex);
	if (ft_pipex(argv, &pipex, argc) == -1)
		return_value = 127;
	mega_free(pipex);
	return (return_value);
}
