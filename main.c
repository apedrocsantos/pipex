/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 15:59:10 by anda-cun          #+#    #+#             */
/*   Updated: 2023/06/23 16:36:56 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	int			i;
	int			j;
	t_pipe	pipe;

	i = 1;
	j = 0;
	while (envp[++i])
		if (ft_strnstr(envp[i], "PATH=", sizeof((envp[i]))))
			pipe.path_list = ft_split(&envp[i++][5], ':');
	pipe.args = (char ***)malloc(sizeof(char ***) * (argc - 2));
	i = 2;
	while (i < argc - 1)
		pipe.args[j++] = ft_split(argv[i++], ' ');
	pipe.args[j] = NULL;
	if(check_path(pipe.path_list, &pipe) == -1)
	{
		ft_printf("FAILED\n");
        mega_free(pipe);
		return -1;
	}
	mega_free(pipe);
}

// /user/bin/cat    which cat
