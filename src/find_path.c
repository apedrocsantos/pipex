/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 09:55:29 by anda-cun          #+#    #+#             */
/*   Updated: 2023/06/28 19:11:59 by anda-cun         ###   ########.fr       */
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

int	check_path(char **paths, t_pipe *pipex)
{
	int		i, j;
	char	*str_to_check;

	i = 0;
	j = 0;
	while (pipex->args[j])
	{
		if (ft_strchr(*pipex->args[j], '/'))
		{
			// ft_printf("accessing %s\n", *pipex->args[j]);
			if (access(*pipex->args[j], X_OK) != 0)
			{
				ft_printf("%s: %s: %s\n", pipex->shell, strerror(errno), *pipex->args[j]);
				mega_free(*pipex);
				return (-1);
			}
			pipex->path[j] = ft_strdup(*pipex->args[j]);
			j++;
		}
		else
		{
			while (paths[i] && pipex->args[j])
			{	
				str_to_check = join_three(paths[i], "/", *pipex->args[j]);
				if (access(str_to_check, X_OK) == 0)
				{
					pipex->path[j++] = str_to_check;
					i = 0;
					break;
				}
				else
				{
					if (!paths[i + 1])
					{
						printf("%s: command not found: %s\n", pipex->shell, *pipex->args[j]);
						mega_free(*pipex);
						free(str_to_check);
						return (-1);
					}
					free(str_to_check);
					i++;
				}
			}
		}
	}
	return (0);
}