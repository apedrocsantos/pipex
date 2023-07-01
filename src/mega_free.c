/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mega_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 11:20:49 by anda-cun          #+#    #+#             */
/*   Updated: 2023/07/01 09:18:47 by anda-cun         ###   ########.fr       */
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
	while (i <= pipex.cmd_nbr)
		free(pipex.fd[i++]);
	free(pipex.fd);
}
