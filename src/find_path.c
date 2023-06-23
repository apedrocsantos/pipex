/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 09:55:29 by anda-cun          #+#    #+#             */
/*   Updated: 2023/06/23 16:39:31 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*join_three(char *s1, char *s2, char *s3)
{
	char	*one;
	char	*two;

	one = ft_strjoin(s1, s2);
	two = ft_strjoin(one, s3);
	free(one);
	ft_printf("%s\n", two);
	return (two);
}

int	check_path(char **paths, t_pipe *pipe)
{
	int		i, j;
	char	*str_to_check;

	i = 0;
	j = 0;
	while (paths[i] && pipe->args[j])
	{
		str_to_check = join_three(paths[i], "/", *pipe->args[j]);
		if (access(str_to_check, X_OK) == 0)
		{
        	*pipe->args[j++] = str_to_check;
			i = 0;
		}
		else
		{
			if (!paths[i + 1])
			{
					free(str_to_check);
					return (-1);
			}
			free(str_to_check);
		}
		i++;
	}
	return (0);
}
