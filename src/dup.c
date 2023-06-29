/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 09:55:29 by anda-cun          #+#    #+#             */
/*   Updated: 2023/06/29 12:50:20 by anda-cun         ###   ########.fr       */
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
	char	*str_to_check;
	int		i;
	int		j;
	int		g;

	j = 0;
	g = 0;
	while (pipex->args[j])
	{
		if (ft_strchr(*pipex->args[j], '/'))
		{
			if (access(*pipex->args[j], X_OK) != 0)
				ft_printf("%s: %s: %s\n", pipex->shell, strerror(errno),
						*pipex->args[j]);
			else
			{
				pipex->path[g] = ft_strdup(*pipex->args[j]);
				g++;
			}
			j++;
		}
		else
		{
			i = 0;
			while (paths[i] && pipex->args[j])
			{
				str_to_check = join_three(paths[i], "/", *pipex->args[j]);
				if (access(str_to_check, X_OK) == 0)
				{
					pipex->path[g++] = str_to_check;
					j++;
				}
				else
				{
					if (!paths[i + 1])
					{
						i = 0;
						printf("%s: command not found: %s\n", pipex->shell,
								*pipex->args[j++]);
					}
					else
						i++;
					free(str_to_check);
				}
			}
		}
	}
	return (0);
}
