/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchappon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 17:01:17 by lchappon          #+#    #+#             */
/*   Updated: 2019/02/11 17:29:50 by lchappon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_floorcasting(t_w3d *e)
{
	if (e->wall.side == 0 && e->ray.dir.x > 0)
	{
		e->floor.wall.x = e->ray.pos.x;
		e->floor.wall.y = e->ray.pos.y + e->wall.hit;
	}
	else if (e->wall.side == 0 && e->ray.dir.x < 0)
	{
		e->floor.wall.x = e->ray.pos.x + 1;
		e->floor.wall.y = e->ray.pos.y + e->wall.hit;
	}
	else if (e->wall.side == 1 && e->ray.dir.y > 0)
	{
		e->floor.wall.x = e->ray.pos.x + e->wall.hit;
		e->floor.wall.y = e->ray.pos.y;
	}
	else
	{
		e->floor.wall.x = e->ray.pos.x + e->wall.hit;
		e->floor.wall.y = e->ray.pos.y + 1;
	}
}

void	ft_wallcasting(t_w3d *e)
{
	e->wall.dist = e->wall.side == 0 ?
		(e->ray.pos.x - e->cam.pos.x + (1 - e->ray.move.x) / 2) / e->ray.dir.x :
		(e->ray.pos.y - e->cam.pos.y + (1 - e->ray.move.y) / 2) / e->ray.dir.y;
	e->wall.height = HEIGHT / e->wall.dist;
	e->wall.top = -e->wall.height / 2;
	e->wall.top -= e->wall.top * e->move.v;
	e->wall.top += HEIGHT / 2 + e->rot.v;
	e->wall.top -= e->wall.height * e->wall.size;
	e->wall.bottom = e->wall.height / 2;
	e->wall.bottom += e->wall.bottom * e->move.v;
	e->wall.bottom += HEIGHT / 2 + e->rot.v;
	e->wall.top = e->wall.top < 0 ? 0 : e->wall.top;
	e->wall.top = e->wall.top > HEIGHT ? HEIGHT : e->wall.top;
	e->wall.bottom = e->wall.bottom < 0 ? 0 : e->wall.bottom;
	e->wall.bottom = e->wall.bottom > HEIGHT ? HEIGHT : e->wall.bottom;
}

void	ft_raycasting(t_w3d *e)
{
	while (e->map[e->ray.pos.y][e->ray.pos.x] <= 0)
	{
		if (e->ray.cast.x < e->ray.cast.y)
		{
			e->ray.cast.x += e->ray.casting.x;
			e->ray.pos.x += e->ray.move.x;
			e->wall.side = 0;
		}
		else
		{
			e->ray.cast.y += e->ray.casting.y;
			e->ray.pos.y += e->ray.move.y;
			e->wall.side = 1;
		}
	}
}

void	ft_raycasting_init(t_w3d *e)
{
	e->screen = (double)2 * e->x / WIDTH - 1;
	e->ray.dir.x = e->cam.dir.x + e->cam.plane.x * e->screen;
	e->ray.dir.y = e->cam.dir.y + e->cam.plane.y * e->screen;
	e->ray.pos.x = (int)e->cam.pos.x;
	e->ray.pos.y = (int)e->cam.pos.y;
	e->ray.move.x = e->ray.dir.x < 0 ? -1 : 1;
	e->ray.move.y = e->ray.dir.y < 0 ? -1 : 1;
	e->ray.casting.x = fabs(1 / e->ray.dir.x);
	e->ray.casting.y = fabs(1 / e->ray.dir.y);
	e->ray.cast.x = e->ray.dir.x < 0 ?
		(e->cam.pos.x - e->ray.pos.x) * e->ray.casting.x :
		(e->ray.pos.x + 1 - e->cam.pos.x) * e->ray.casting.x;
	e->ray.cast.y = e->ray.dir.y < 0 ?
		(e->cam.pos.y - e->ray.pos.y) * e->ray.casting.y :
		(e->ray.pos.y + 1 - e->cam.pos.y) * e->ray.casting.y;
}
