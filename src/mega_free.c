/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mega_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 11:20:49 by anda-cun          #+#    #+#             */
/*   Updated: 2023/06/27 22:11:17 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	mega_free(t_pipe pipex)
{
	int	i;
	int	j;

	i = 0;
	while (pipex.args[i])
	{
		j = 0;
		while (pipex.args[i][j])
			free(pipex.args[i][j++]);
		free(pipex.args[i++]);
	}
	free(pipex.args);
	i = 0;
	while (pipex.path_list[i])
		free(pipex.path_list[i++]);
	free(pipex.path_list);
	i = 0;
	while (pipex.path[i])
		free(pipex.path[i++]);
	free(pipex.path);
}
