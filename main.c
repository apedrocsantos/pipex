/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 15:59:10 by anda-cun          #+#    #+#             */
/*   Updated: 2023/06/25 16:55:29 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	int			i;
	int			j;
	t_pipe	pipe;

	i = -1;
	while (envp[++i])
	{
		if (ft_strnstr(envp[i], "PATH=", sizeof((envp[i]))))
			pipe.path_list = ft_split(&envp[i][5], ':');
		if (ft_strnstr(envp[i], "SHELL=", sizeof((envp[i]))))
		{
			pipe.shell = ft_strrchr(envp[i], '/');
			pipe.shell++;
		}
	}
	pipe.args = (char ***)malloc(sizeof(char ***) * (argc - 2));
	i = 2;
	j = 0;
	while (i < argc - 1)
		pipe.args[j++] = ft_split(argv[i++], ' ');
	pipe.args[j] = NULL;
	if(check_path(pipe.path_list, &pipe) == -1)
		return(127);
	i = 0;
	mega_free(pipe);
}