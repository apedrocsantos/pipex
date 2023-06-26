/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 15:59:10 by anda-cun          #+#    #+#             */
/*   Updated: 2023/06/26 17:20:29 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/pipex.h"

void	get_paths(char *envp[], t_pipe *pipe)
{
	int i = -1;
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

int		ft_pipex(char *argv[], t_pipe *pipex, int argc)
{
	int i = 0;
	int	fd[argc - 2][2];
	int	pid[argc - 3];
	
	while(i < argc - 2)
		pipe(fd[i++]);
	fd[0][0] = open(argv[1], O_CREAT | O_RDONLY);
	dup2(fd[0][0], STDIN_FILENO);
	fd[argc - 2][1] = open(argv[argc - 1], O_CREAT | O_WRONLY, 00755);
	// dup2(fd[argc - 2][1], STDOUT_FILENO);
	i = 0;
	while (i < argc - 3)
	{
		pid[i] = fork();
		if (pid[i] == 0)
		{
			dup2(fd[i][0], STDIN_FILENO);
			// dup2(fd[i + 1][1], STDOUT_FILENO);
			execve(pipex->args[i][0], pipex->args[i], NULL);	
		}
		waitpid(pid[i], NULL, 0);
		ft_printf("dad here\n");
		i++;
		close(fd[i][0]);
		close(fd[i + 1][1]);
	}
	return (0);
}

int	main(int argc, char *argv[], char *envp[])
{
	int			i;
	int			j;
	t_pipe	pipex;

	get_paths(envp, &pipex);
	pipex.args = (char ***)malloc(sizeof(char ***) * (argc - 2));
	i = 2;
	j = 0;
	while (i < argc - 1)
		pipex.args[j++] = ft_split(argv[i++], ' ');
	pipex.args[j] = NULL;
	if(check_path(pipex.path_list, &pipex) == -1)
		return(127);
	i = 0;
	ft_pipex(argv, &pipex, argc);
	mega_free(pipex);
}