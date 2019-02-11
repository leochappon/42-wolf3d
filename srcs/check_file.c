/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchappon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 17:00:27 by lchappon          #+#    #+#             */
/*   Updated: 2018/12/11 16:28:32 by lchappon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		ft_alloc_chars(t_w3d *e, char *line, int y)
{
	int		x;
	char	**tab;

	x = 0;
	tab = ft_strsplit(line, ' ');
	if (!(e->map[y] = ft_memalloc(sizeof(int) * e->size.x)))
	{
		free(line);
		free(tab);
		return (-1);
	}
	while (tab[x])
	{
		e->map[y][x] = ft_atoi(tab[x]);
		if (e->map[y][x] == -1 && e->cam.pos.x == 0 && e->cam.pos.y == 0)
		{
			e->cam.pos.x = x + 0.5;
			e->cam.pos.y = y + 0.5;
		}
		free(tab[x]);
		x++;
	}
	free(line);
	free(tab);
	return (0);
}

int		ft_check_lines_length(t_w3d *e, char *line)
{
	int		x;
	char	**tab;

	x = 0;
	tab = ft_strsplit(line, ' ');
	while (tab[x])
	{
		free(tab[x]);
		x++;
	}
	free(line);
	free(tab);
	if (e->size.y == 0)
		e->size.x = x;
	else if (x != e->size.x)
	{
		ft_putendl("error: map structure is invalid.");
		return (-1);
	}
	e->size.y++;
	return (0);
}

int		ft_alloc_lines(t_w3d *e)
{
	char	*line;

	e->size.x = 0;
	e->size.y = 0;
	e->fd = open(e->file, O_RDONLY);
	while (get_next_line(e->fd, &line) > 0)
	{
		if (ft_check_lines_length(e, line) == -1)
		{
			close(e->fd);
			return (-1);
		}
	}
	if (!(e->map = ft_memalloc(sizeof(int *) * e->size.y)))
		return (-1);
	close(e->fd);
	return (0);
}

int		ft_check_file(t_w3d *e)
{
	char	*line;
	int		y;
	int		ret;

	y = 0;
	if (ft_alloc_lines(e) == -1)
		return (-1);
	e->fd = open(e->file, O_RDONLY);
	while ((ret = get_next_line(e->fd, &line)) > 0)
	{
		if (ft_alloc_chars(e, line, y) == -1)
		{
			close(e->fd);
			return (-1);
		}
		y++;
	}
	close(e->fd);
	return ((ret == -1) ? -1 : 0);
}
