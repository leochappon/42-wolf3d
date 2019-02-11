/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchappon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/17 14:51:34 by lchappon          #+#    #+#             */
/*   Updated: 2018/05/09 18:41:30 by lchappon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int			end(char *buff)
{
	int				count;

	count = 0;
	while (buff[count] != '\n' && buff[count])
		count++;
	if (buff[count] == '\n')
	{
		buff[count] = '\0';
		return (count);
	}
	else
		return (-1);
}

static char			*middle(char *buff, char *tmp)
{
	size_t			i;
	size_t			j;
	char			*ptr;

	i = 0;
	j = 0;
	if (buff)
		i = ft_strlen(buff);
	if (tmp)
		j = ft_strlen(tmp);
	ptr = (char *)malloc(sizeof(*ptr) * (i + j + 1));
	if (ptr == NULL)
		return (NULL);
	ft_memcpy(ptr, buff, i);
	ft_memcpy(ptr + i, tmp, j);
	ptr[i + j] = '\0';
	free(buff);
	ft_bzero(tmp, BUFF_SIZE + 1);
	return (ptr);
}

static int			start(char **buff, char **tmp, char **line)
{
	char			*ptr;
	int				final;

	*buff = middle(*buff, *tmp);
	final = end(*buff);
	if (final > -1)
	{
		*line = ft_strdup(*buff);
		ptr = *buff;
		*buff = ft_strdup(*buff + final + 1);
		free(ptr);
		return (1);
	}
	return (0);
}

static int			free_return(char *tmp, int ret)
{
	free(tmp);
	return (ret);
}

int					get_next_line(int const fd, char **line)
{
	static char		*buff[BUFF_SIZE];
	char			*tmp;
	int				result;

	tmp = ft_strnew(BUFF_SIZE);
	if (fd < 0 || !line || BUFF_SIZE <= 0 || read(fd, tmp, 0) < 0)
		return (free_return(tmp, -1));
	while (read(fd, tmp, BUFF_SIZE) > 0)
	{
		result = start(&buff[fd], &tmp, line);
		free(tmp);
		if (result == 1)
			return (1);
		tmp = ft_strnew(BUFF_SIZE);
	}
	if ((result = start(&buff[fd], &tmp, line)))
		return (free_return(tmp, 1));
	else if (ft_strlen(buff[fd]) > 0)
	{
		*line = ft_strdup(buff[fd]);
		ft_strdel(&buff[fd]);
		return (1);
	}
	free(tmp);
	return (0);
}
