/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchappon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 17:11:57 by lchappon          #+#    #+#             */
/*   Updated: 2019/02/11 18:19:53 by lchappon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		ft_mouse_motion(int x, int y, t_w3d *e)
{
	if (e->mouse == 1)
	{
		mlx_mouse_hide();
		e->rot.speed = 0.002 * (x - WIDTH / 2);
		e->rot.v -= (y - HEIGHT / 2);
		if (e->rot.v < -HEIGHT / 2)
			e->rot.v = -HEIGHT / 2;
		if (e->rot.v > HEIGHT / 2)
			e->rot.v = HEIGHT / 2;
		mlx_mouse_move(e->win, WIDTH / 2, HEIGHT / 2);
	}
	return (0);
}

void	ft_key_rotate(int keycode, t_w3d *e, int value)
{
	if (keycode == 126)
		e->rot.up = value;
	if (keycode == 125)
		e->rot.down = value;
	if (keycode == 124)
		e->rot.right = value;
	if (keycode == 123)
		e->rot.left = value;
}

void	ft_key_move(int keycode, t_w3d *e, int value)
{
	if (keycode == 13)
		e->move.forward = value;
	if (keycode == 1)
		e->move.backward = value;
	if (keycode == 2)
		e->move.right = value;
	if (keycode == 0)
		e->move.left = value;
}

int		ft_key_release(int keycode, t_w3d *e)
{
	ft_key_move(keycode, e, 0);
	ft_key_rotate(keycode, e, 0);
	if (keycode == 53)
		ft_close(e);
	if (keycode == 257)
		e->move.sprint = 0;
	if (keycode == 49)
		e->move.up = 0;
	if (keycode == 8)
		e->move.down = 0;
	if (keycode == 3)
		e->move.fly = e->move.fly == 0 ? 1 : 0;
	if (keycode == 48)
		e->info = e->info == 0 ? 1 : 0;
	if (keycode == 46)
		e->mouse = e->mouse == 0 ? 1 : 0;
	return (0);
}

int		ft_key_press(int keycode, t_w3d *e)
{
	ft_key_move(keycode, e, 1);
	ft_key_rotate(keycode, e, 1);
	if (keycode == 257 && e->move.down == 0)
		e->move.sprint = 1;
	if (keycode == 49 && e->move.up == 0 &&
			(e->move.v <= 0 || e->move.fly == 1) && e->move.down == 0)
	{
		e->move.up = 1;
		e->move.up2 = 1;
	}
	if (keycode == 8 && e->move.up == 0)
		e->move.down = 1;
	if (keycode == 69 && e->wall.size < 2)
		e->wall.size++;
	if (keycode == 78 && e->wall.size > 0 && e->move.v < e->wall.size)
		e->wall.size--;
	return (0);
}
