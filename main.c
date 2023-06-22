/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 15:59:10 by anda-cun          #+#    #+#             */
/*   Updated: 2023/06/22 22:36:34 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int	main(int argc, char *argv[])
{
	int		i;
	int		j;
	char	***commands;

	commands = (char ***)malloc(sizeof(char) * (argc - 3));
	i = 1;
	j = 0;
	while (i < argc - 2)
	{
		commands[j] = ft_split(argv[i], ' ');
		ft_printf("%s\n", commands[j][0]);
		i++;
	}
	i = 0;
	j = 0;
	while (commands[i])
	{
		ft_printf("%s\n", commands[i++][0]);
	}
}

// /user/bin/cat    which cat
