/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 15:59:10 by anda-cun          #+#    #+#             */
/*   Updated: 2023/06/23 13:14:07 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/pipex.h"



int	main(int argc, char *argv[], char *envp[])
{
	int		i;
	int		j;
    pipe_list pipe;
    
	i = 2;
	j = 0;
    while (envp[i])
    {
        if (ft_strnstr(envp[i], "PATH=", sizeof((envp[i]))))
            pipe.path_list = ft_split(&envp[i][5], ':');
        i++;
    }
    pipe.commands = (char ***)malloc(sizeof(char ***) * (argc - 2));
    i = 2;
	while (i < argc - 1)
		pipe.commands[j++] = ft_split(argv[i++], ' ');
    pipe.commands[j] = NULL;
    pipe.path = check_path(pipe.path_list, pipe.commands[0][0]);
    ft_printf("%s\n", pipe.path);
    mega_free(pipe);
}

// /user/bin/cat    which cat
