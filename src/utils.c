/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 20:01:51 by anda-cun          #+#    #+#             */
/*   Updated: 2023/07/02 11:06:01 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	close_fds(t_pipe *pipex)
{
	int	i;

	i = pipex->cmd_nbr;
	while (i--)
	{
		// ft_printf("closing %d and %d\n", pipex->fd[i][0], pipex->fd[i][1]);
		if (close(pipex->fd[i][0]) == -2)
			ft_printf("error closing fd[%d][0]\n", i);
		if (close(pipex->fd[i][1]) == -2)
			ft_printf("error closing fd[%d][1]\n", i);
		if (pipex->outfile != -1)
		{
			if (close(pipex->outfile) == -2)
				ft_printf("error closing outfile %d\n", pipex->outfile);
		}
	}
}

void	write_error(t_pipe *pipex, char *arg)
{
	char	*str;
	char	*str2;
	char	*error;

	error = ft_strdup(strerror(errno));
	*error += 32;
	str = join_three(pipex->shell, ": ", error);
	str2 = join_three(str, ": ", arg);
	ft_putendl_fd(str2, 2);
	free(str);
	free(str2);
	free(error);
}

int	count_words(char *str)
{
	int	i;

	i = 0;
	while (*str)
	{
		if (*str == ' ')
			str++;
		if (*str == '\'')
		{
			i++;
			str++;
			while (*str && *str != '\'')
				str++;
		}
		else
		{
			i++;
			while (*str && *str != ' ')
				str++;
		}
		str++;
	}
	return (i);
}

char	**split_args(char *str)
{
	int	i;
	int g;
	int	len;
	char	**arr;

	i = 0;
	g = 0;
	arr = (char **)malloc(sizeof(char**) * (count_words(str) + 1));
	while (str[i])
	{
		ft_printf("here:%\t%c\n", str[i]);
		len = 0;
		while (str[i] == ' ')
			i++;
		if (str[i] == '\'')
		{
			i++;
			while (str[i + len] && str[i + len] != '\'')
				len++;
		}
		else
			while (str[i + len] && str[i + len] != ' ')
				len++;
		arr[g] = ft_substr(str, i, len);
		ft_printf("%s\n", arr[g]);
		g++;
		i += len;
	}
	arr[g] = NULL;
	return(arr);
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
