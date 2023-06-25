/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 09:55:29 by anda-cun          #+#    #+#             */
/*   Updated: 2023/06/25 23:33:22 by anda-cun         ###   ########.fr       */
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
	return (two);
}

// int	finder(char **paths, t_pipe *pipe)
// {
// 	int i = 0;
// 	char *str_to_check;
	
// 	while (paths[i])
// 	{	
// 		str_to_check = join_three(paths[i], "/", *pipe->args[j]);
// 		if (access(str_to_check, X_OK) == 0)
// 		{
// 			free(*pipe->args[j]);
//         	*pipe->args[j++] = str_to_check;
// 			i = 0;
// 		}
// 	}
// }

int	check_path(char **paths, t_pipe *pipe)
{
	int		i, j;
	char	*str_to_check;

	i = 0;
	j = 0;
	if (ft_strchr(*pipe->args[j], '/'))
		{
			if (access(*pipe->args[j], X_OK) != 0)
			{
				str_to_check = ft_strdup(*pipe->args[j]);
				ft_printf("%s: %s: %s\n", pipe->shell, strerror(errno), str_to_check);
				free(str_to_check);
			}
		}
	else
	{
	while (paths[i])
	{	
		str_to_check = join_three(paths[i], "/", *pipe->args[j]);
		if (access(str_to_check, X_OK) == 0)
		{
			free(*pipe->args[j]);
        	*pipe->args[j++] = str_to_check;
			i = 0;
		}
		else
		{
			if (!paths[i + 1])
			{
				printf("%s: command not found: %s\n", pipe->shell, *pipe->args[j]);
        		mega_free(*pipe);
				free(str_to_check);
				return (-1);
			}
			free(str_to_check);
		}
		i++;
	}
	}
	return (0);
}
