/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mega_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 11:20:49 by anda-cun          #+#    #+#             */
/*   Updated: 2023/06/25 15:10:57 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	mega_free(t_pipe pipe)
{
	int	i;
	int	j;

	i = 0;
	while (pipe.args[i])
	{
		j = 0;
		while (pipe.args[i][j])
			free(pipe.args[i][j++]);
		free(pipe.args[i++]);
	}
	free(pipe.args);
	i = 0;
	while (pipe.path_list[i])
		free(pipe.path_list[i++]);
	free(pipe.path_list);
}
