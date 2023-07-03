/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 20:01:51 by anda-cun          #+#    #+#             */
/*   Updated: 2023/07/03 19:09:55 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	close_fds(t_pipe *pipex, int j)
{
	int	i;
	int	fd_no;

	i = pipex->cmd_nbr;
	while (i--)
	{
		fd_no = close(pipex->fd[i][0]);
		if (fd_no == -1)
			ft_printf("error closing fd[%d][0]: %d\n", i, pipex->fd[i][0]);
		if (i > j)
		{
			fd_no = close(pipex->fd[i][1]);
			if (fd_no == -1)
				ft_printf("error closing fd[%d][1]: %d\n", i, pipex->fd[i][0]);
		}
	}
}

void	write_error(t_pipe *pipex, char *arg)
{
	char	*str;
	char	*str2;
	char	*error;

	ft_printf("errno: %d\n", errno);
	error = ft_strdup(strerror(errno));
	*error += 32;
	// if (!ft_strchr(arg, '/') && ft_strncmp())
	// {
	// 	free(error);
	// 	error = ft_strdup("command not found");
	// }
	str = join_three(pipex->shell, ": ", error);
	str2 = join_three(str, ": ", arg);
	ft_putendl_fd(str2, 2);
	free(str);
	free(str2);
	free(error);
}

int	count_words(char *str)
{
	int		i;
	char	c;

	i = 0;
	while (*str)
	{
		c = ' ';
		while (*str == ' ')
			str++;
		if (!*str)
			break ;
		if (*str == '\'')
		{
			str++;
			c = '\'';
		}
		i++;
		while (*str && *str != c)
			str++;
		if (c != ' ')
			str++;
	}
	return (i);
}

char	**split_args(char *str)
{
	char	**arr;
	int		i;
	int		g;
	int		len;
	char	c;

	i = 0;
	g = 0;
	arr = (char **)ft_calloc(count_words(str) + 1, sizeof(char **));
	while (str[i])
	{
		c = ' ';
		len = 0;
		while (str[i] == ' ')
			i++;
		if (!str[i])
			break ;
		if (str[i] == '\'')
		{
			i++;
			c = '\'';
		}
		while (str[i + len] && str[i + len] != c)
			len++;
		arr[g++] = ft_substr(str, i, len);
		i += len;
		if (c != ' ')
			i++;
	}
	return (arr);
}

char	*join_three(char *s1, char *s2, char *s3)
{
	char	*one;
	char	*two;

	one = ft_strjoin(s1, s2);
	two = ft_strjoin(one, s3);
	free(one);
	return (two);
}
