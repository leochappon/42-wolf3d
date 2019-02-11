/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchappon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 17:01:32 by lchappon          #+#    #+#             */
/*   Updated: 2019/02/11 18:24:13 by lchappon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_put_texture(t_w3d *e, int x, int y, int tex_w)
{
	if (e->x < WIDTH && e->y < HEIGHT)
	{
		e->data[((e->y * WIDTH + e->x) * 4)] =
			e->tex[e->num].data[((y * tex_w + x) * 4)];
		e->data[((e->y * WIDTH + e->x) * 4) + 1] =
			e->tex[e->num].data[((y * tex_w + x) * 4) + 1];
		e->data[((e->y * WIDTH + e->x) * 4) + 2] =
			e->tex[e->num].data[((y * tex_w + x) * 4) + 2];
	}
}

void	ft_ceiling(t_w3d *e)
{
	e->num = 0;
	e->y = 0;
	while (e->y < e->wall.top)
	{
		e->floor.dist = HEIGHT / (2 * e->y - HEIGHT - 2 * e->rot.v);
		e->floor.weight = e->floor.dist * (2 * e->wall.size + 1) /
			e->wall.dist * (e->move.v / (2 * e->wall.size + 1) - 1);
		e->floor.tile.x = e->floor.weight * e->floor.wall.x +
			(1 - e->floor.weight) * e->cam.pos.x;
		e->floor.tile.y = e->floor.weight * e->floor.wall.y +
			(1 - e->floor.weight) * e->cam.pos.y;
		e->floor.tex.x = (int)(e->floor.tile.x * TEX_W) % TEX_W;
		e->floor.tex.y = (int)(e->floor.tile.y * TEX_H) % TEX_H;
		ft_put_texture(e, e->floor.tex.x, e->floor.tex.y, TEX_W);
		e->y++;
	}
}

void	ft_floor(t_w3d *e)
{
	e->num = 0;
	e->y = e->wall.bottom;
	while (e->y < HEIGHT)
	{
		e->floor.dist = HEIGHT / (2 * e->y - HEIGHT - 2 * e->rot.v);
		e->floor.weight = e->floor.dist / e->wall.dist * (e->move.v + 1);
		e->floor.tile.x = e->floor.weight * e->floor.wall.x +
			(1 - e->floor.weight) * e->cam.pos.x;
		e->floor.tile.y = e->floor.weight * e->floor.wall.y +
			(1 - e->floor.weight) * e->cam.pos.y;
		e->floor.tex.x = (int)(e->floor.tile.x * TEX_W) % TEX_W;
		e->floor.tex.y = (int)(e->floor.tile.y * TEX_H) % TEX_H;
		e->floor.tex.y = abs(e->floor.tex.y);
		ft_put_texture(e, e->floor.tex.x, e->floor.tex.y, TEX_W);
		e->y++;
	}
}

void	ft_walls(t_w3d *e)
{
	if (e->wall.side == 0 && e->ray.dir.x > 0)
		e->num = 1;
	if (e->wall.side == 0 && e->ray.dir.x < 0)
		e->num = 2;
	if (e->wall.side == 1 && e->ray.dir.y > 0)
		e->num = 3;
	if (e->wall.side == 1 && e->ray.dir.y < 0)
		e->num = 4;
	e->wall.hit = e->wall.side == 0 ?
		e->cam.pos.y + e->wall.dist * e->ray.dir.y :
		e->cam.pos.x + e->wall.dist * e->ray.dir.x;
	e->wall.hit -= (int)e->wall.hit;
	e->wall.tex.x = (int)(e->wall.hit * TEX_W) % TEX_W;
	e->y = e->wall.top;
	while (e->y < e->wall.bottom)
	{
		e->wall.tex.y = (e->y - HEIGHT / 2 + (e->wall.height / 2)
				* (-e->move.v + 1)) - e->rot.v;
		e->wall.tex.y = (e->wall.tex.y * TEX_H) / e->wall.height;
		e->wall.tex.y %= TEX_H;
		if (e->wall.tex.y < 0)
			e->wall.tex.y += TEX_H - 1;
		ft_put_texture(e, e->wall.tex.x, e->wall.tex.y, TEX_W);
		e->y++;
	}
}
