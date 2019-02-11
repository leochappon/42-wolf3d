/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchappon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 17:00:59 by lchappon          #+#    #+#             */
/*   Updated: 2019/02/11 18:20:26 by lchappon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_info(t_w3d *e)
{
	if (e->info == 0)
		mlx_string_put(e->mlx, e->win, 10, 5, 0xFFFFFF,
				"Press tab to show commands");
	else
	{
		mlx_string_put(e->mlx, e->win, 10, 5, 0xFFFFFF,
				"MOVE = W A S D");
		mlx_string_put(e->mlx, e->win, 10, 25, 0xFFFFFF,
				"ROTATE = ^ v < > / mouse");
		if (e->mouse == 1)
			mlx_string_put(e->mlx, e->win, 10, 45, 0xFFFFFF, "MOUSE = M (on)");
		else
			mlx_string_put(e->mlx, e->win, 10, 45, 0xFFFFFF, "MOUSE = M (off)");
		mlx_string_put(e->mlx, e->win, 10, 65, 0xFFFFFF, "SPRINT = shift");
		mlx_string_put(e->mlx, e->win, 10, 85, 0xFFFFFF, "JUMP = space");
		mlx_string_put(e->mlx, e->win, 10, 105, 0xFFFFFF, "CROUCH = C");
		mlx_string_put(e->mlx, e->win, 10, 125, 0xFFFFFF, "FLY = F");
		mlx_string_put(e->mlx, e->win, 10, 145, 0xFFFFFF, "WALL = + -");
		mlx_string_put(e->mlx, e->win, 10, 165, 0xFFFFFF, "QUIT = esc");
	}
}

void	*ft_raycast(void *tab)
{
	t_w3d	e;

	e = *(t_w3d *)tab;
	while (e.x < e.xx)
	{
		ft_raycasting_init(&e);
		ft_raycasting(&e);
		ft_wallcasting(&e);
		ft_walls(&e);
		ft_floorcasting(&e);
		ft_floor(&e);
		ft_ceiling(&e);
		e.x++;
	}
	return (0);
}

void	ft_pthread(t_w3d *e)
{
	t_w3d		tab[4];
	pthread_t	t[4];
	int			i;

	i = 0;
	while (i < 4)
	{
		ft_memcpy((void*)&tab[i], (void*)e, sizeof(t_w3d));
		tab[i].x = i * (WIDTH / 4 + 1);
		tab[i].xx = (i + 1) * (WIDTH / 4 + 1);
		i++;
	}
	i = 0;
	while (i < 4)
	{
		pthread_create(&t[i], NULL, ft_raycast, &tab[i]);
		i++;
	}
	i = 0;
	while (i < 4)
	{
		pthread_join(t[i], NULL);
		i++;
	}
}

int		ft_draw(t_w3d *e)
{
	e->img = mlx_new_image(e->mlx, WIDTH, HEIGHT);
	e->data = mlx_get_data_addr(e->img, &(e->bpp), &(e->s_l), &(e->endian));
	ft_pthread(e);
	ft_move(e);
	ft_rotate(e);
	mlx_clear_window(e->mlx, e->win);
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
	if (WIDTH >= 300 && HEIGHT >= 200)
		ft_info(e);
	mlx_destroy_image(e->mlx, e->img);
	return (0);
}
