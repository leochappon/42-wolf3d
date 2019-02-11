/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchappon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 17:00:39 by lchappon          #+#    #+#             */
/*   Updated: 2019/02/11 17:36:03 by lchappon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_free_map(t_w3d *e)
{
	int		y;

	y = 0;
	while (y < e->size.y)
	{
		free(e->map[y]);
		y++;
	}
	free(e->map);
}

int		ft_check_borders(t_w3d *e, int ret)
{
	int		i;

	i = 0;
	while (i < e->size.x)
	{
		if (e->map[0][i] <= 0 || e->map[e->size.y - 1][i] <= 0)
			ret = -1;
		i++;
	}
	i = 0;
	while (i < e->size.y)
	{
		if (e->map[i][0] <= 0 || e->map[i][e->size.x - 1] <= 0)
			ret = -1;
		i++;
	}
	return (ret);
}

int		ft_check_map(t_w3d *e)
{
	int		ret;

	ret = 0;
	ret = ft_check_borders(e, ret);
	if (e->cam.pos.x == 0 && e->cam.pos.y == 0)
		ret = -1;
	if (ret == -1)
		ft_free_map(e);
	if (ret == -1)
		ft_putendl("error: map elements are invalid");
	return (ret);
}
