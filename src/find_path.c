/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 09:55:29 by anda-cun          #+#    #+#             */
/*   Updated: 2023/06/23 13:08:37 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char    *join_three(char *s1, char *s2, char *s3)
{
    char *one;
    char *two;

    one = ft_strjoin(s1, s2);
    two = ft_strjoin(one, s3);
    free(one);
    return(two);
}

char    *check_path(char **paths, char *command)
{
    int i = 0;
    while (paths[i])
    {
        char *str_to_check = join_three(paths[i], "/", command);
        if (access(str_to_check, X_OK) == 0)
            return(str_to_check);
        free (str_to_check);
        i++;
    }
    return (NULL);
}