/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaoud <msaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 17:01:47 by msaoud            #+#    #+#             */
/*   Updated: 2021/12/15 00:28:43 by msaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_check(char *select, char *str)
{
	if (select[0] == '\0')
	{
		free(select);
		free(str);
		return (NULL);
	}
	else
		return (select);
}

char	*ft_select(char *str)
{
	int		i;
	char	*beforen;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	beforen = malloc(i + 2);
	if (!beforen)
		return (NULL);
	i = -1;
	while (str[++i] && str[i] != '\n')
		beforen[i] = str[i];
	if (str[i] == '\n')
		beforen[i++] = '\n';
	beforen[i] = '\0';
	return (beforen);
}

char	*ft_rest(char *str)
{
	int		i;
	int		j;
	char	*rest;

	i = 0;
	j = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\0')
	{
		free(str);
		return (NULL);
	}
	rest = malloc(ft_strlen(str) - i + 1);
	if (!rest)
		return (NULL);
	i++;
	while (str[i])
		rest[j++] = str[i++];
	rest[j] = '\0';
	free(str);
	return (rest);
}

char	*ft_read(int fd, char *str, char *buff)
{
	int	rd;

	rd = 1;
	while (!(ft_strchr (str, '\n')) && rd > 0)
	{
		rd = read(fd, buff, BUFFER_SIZE);
		if (rd == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[rd] = '\0';
		str = ft_strjoin(str, buff);
	}
	free(buff);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*str[256];
	int			rd;
	char		*buff;
	char		*select;

	rd = 1;
	if (fd < 0 || fd > 256)
		return (NULL);
	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	str[fd] = ft_read(fd, str[fd], buff);
	if (!str[fd])
		return (NULL);
	select = ft_select(str[fd]);
	str[fd] = ft_rest(str[fd]);
	if (!(ft_check(select, str[fd])))
		return (NULL);
	return (select);
}
