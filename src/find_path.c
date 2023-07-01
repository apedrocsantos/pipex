/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 09:55:29 by anda-cun          #+#    #+#             */
/*   Updated: 2023/07/01 20:30:26 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	check_full_path(t_pipe *pipex, int j)
{
	if (access(*pipex->args[j], X_OK) != 0)
		write_error(pipex, *pipex->args[j]);
}

int	check_path(t_pipe *pipex, int j)
{
	int		i;
	char	*str_to_check;

	i = 0;
	while (pipex->path_list[i])
	{
		str_to_check = join_three(pipex->path_list[i], "/", *pipex->args[j]);
		if (access(str_to_check, X_OK) == 0)
		{
			free(*pipex->args[j]);
			*pipex->args[j++] = str_to_check;
			break ;
		}
		if (!pipex->path_list[i + 1])
		{
			write_error(pipex, *pipex->args[j]);
			free(str_to_check);
			break ;
		}
		i++;
		free(str_to_check);
	}
	return (0);
}

int	check_paths(t_pipe *pipex)
{
	int	j;

	j = 0;
	while (pipex->args[j])
	{
		if (ft_strchr(*pipex->args[j], '/'))
			check_full_path(pipex, j);
		else
			check_path(pipex, j);
		j++;
	}
	return (0);
}
