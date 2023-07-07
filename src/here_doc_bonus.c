/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 13:58:33 by anda-cun          #+#    #+#             */
/*   Updated: 2023/07/07 16:01:23 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

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

int	here_doc(int fd, char *delim)
{
	char	*str;

	str = "";
	delim = create_delimiter(delim, "\n");
	while (str)
	{
		str = get_next_line(STDIN_FILENO);
		if (!str)
			break ;
		if (!ft_strncmp(str, delim, ft_strlen(delim)))
		{
			close(fd);
			free(str);
			free(delim);
			return (0);
		}
		write(fd, str, ft_strlen(str));
		free(str);
	}
	free(delim);
	return (1);
}
