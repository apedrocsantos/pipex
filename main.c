/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 15:59:10 by anda-cun          #+#    #+#             */
/*   Updated: 2023/06/19 16:40:05 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "libft.h"

int main(int argc, char *argv[], char *envp[])
{
    int i = 0;
    char **commands[--argc/2];
    
    argv++;
    while (argc - i > 0)
    {
        if (argc % 2 == 0)
            commands[i] = ft_split(argv[i], ' ');
        i++;
    }
    i = 0;
    // while (commands[i])
        ft_printf("%s\n", *commands[0]);
}

// /user/bin/cat    which cat