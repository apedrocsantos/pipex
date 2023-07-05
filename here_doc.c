/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 13:58:33 by anda-cun          #+#    #+#             */
/*   Updated: 2023/07/04 16:09:05 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"
#include <stdio.h>

char	*create_delimiter(char *s1, char *s2)
{
	int		i;
	int		j;
	int		size;
	char	*str;

	size = ft_strlen(s1) + ft_strlen(s2);
	str = (char *)ft_calloc(size + 1, sizeof(char *));
	i = -1;
	while (s1[++i])
		str[i] = s1[i];
	j = -1;
	while (s2[++j])
		str[i + j] = s2[j];
	return (str);
}

void	here_doc(int fdin, char *delim)
{
	char	*str;
	int		flag;
	// int 	fd[2];

	str = "";
	delim = create_delimiter(delim, "\n");
	flag = 0;
	// pipe(fd);
	while (str)
	{
		str = get_next_line(fdin);
		if (!str)
			break ;
		if (!ft_strncmp(str, delim, ft_strlen(delim)))
		{
			close(fdin);
			free(str);
			free(delim);
			exit (0);
		}
		free(str);
	}
}

// int	main(void)
// {
// 	here_doc("hi");
// }
