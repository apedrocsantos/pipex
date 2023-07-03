#include "includes/pipex.h"
#include <stdio.h>

int	main(void)
{
	char	*str;
	int		i;
	int		len;
	char	c;

	c = ' ';
	i = 0;
	str = "oh 'hi there'  a ";
	while (str[i])
	{
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
		printf("%s\n", ft_substr(str, i, len));
		i += len;
		if (str[i] == c)
			i++;
	}
}
