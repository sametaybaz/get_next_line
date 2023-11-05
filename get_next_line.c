/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaybaz <aaybaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 17:53:31 by aaybaz            #+#    #+#             */
/*   Updated: 2022/12/01 18:00:08 by aaybaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
//#include <stdio.h>
//#include <fcntl.h>

static char	*left_str(char *line, char c)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (line[i] != '\0' && line[i] != c)
		i++;
	if (!line[i])
	{
		free(line);
		return (NULL);
	}
	str = (char *)malloc((ft_strlen(line) - i));
	if (!str)
		return (NULL);
	i++;
	while (line[i] != '\0')
		str[j++] = line[i++];
	str[j] = '\0';
	free(line);
	return (str);
}

static char	*new_line(char *line, char c)
{
	char	*str;
	int		i;

	i = 0;
	if (!line[i])
		return (NULL);
	while (line[i] != '\0' && line[i] != c)
		i++;
	str = (char *)malloc(sizeof(char) * (i + 2));
	if (!str)
		return (NULL);
	i = 0;
	while (line[i] != '\0' && line[i] != c)
	{
		str[i] = line[i];
		i++;
	}
	if (line[i] == c)
	{
		str[i] = line[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static char	*read_line(int fd, char *line)
{
	char	*tmp;
	int		i;

	tmp = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!tmp)
		return (NULL);
	i = 1;
	while (!ft_strchr(line, '\n') && i != 0)
	{
		i = read(fd, tmp, BUFFER_SIZE);
		if (i == -1)
		{
			free(tmp);
			return (NULL);
		}
		tmp[i] = '\0';
		line = ft_strjoin(line, tmp);
	}
	free(tmp);
	return (line);
}

char	*get_next_line(int fd)
{
	char		*str;
	static char	*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = read_line(fd, line);
	if (line)
	{
		str = new_line(line, '\n');
		line = left_str(line, '\n');
		return (str);
	}
	return (NULL);
}

/* int	main(void)
{
	int	k;
	int	j;
	int	i;

	k = open(".o", O_RDONLY);
	j = open(".o_2", O_RDONLY);
	i = 0;
	while (i < 2)
	{
		printf("%s", get_next_line(k));
		printf("%s", get_next_line(j));
		i++;
	}
	close(k);
	close(j);
} */
