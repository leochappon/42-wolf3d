/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchappon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 14:46:35 by lchappon          #+#    #+#             */
/*   Updated: 2019/02/11 18:17:58 by lchappon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		ft_close(t_w3d *e)
{
	ft_free_map(e);
	exit(0);
	return (0);
}

void	ft_tex_init(t_w3d *e)
{
	int		x;
	int		y;

	x = TEX_W;
	y = TEX_H;
	e->tex[0].img = mlx_xpm_file_to_image(e->mlx, "textures/wood.xpm",
			&x, &y);
	e->tex[0].data = mlx_get_data_addr(e->tex[0].img, &e->tex[0].bpp,
			&e->tex[0].s_l, &e->tex[0].endian);
	e->tex[1].img = mlx_xpm_file_to_image(e->mlx, "textures/redbrick.xpm",
			&x, &y);
	e->tex[1].data = mlx_get_data_addr(e->tex[1].img, &e->tex[1].bpp,
			&e->tex[1].s_l, &e->tex[1].endian);
	e->tex[2].img = mlx_xpm_file_to_image(e->mlx, "textures/bluestone.xpm",
			&x, &y);
	e->tex[2].data = mlx_get_data_addr(e->tex[2].img, &e->tex[2].bpp,
			&e->tex[2].s_l, &e->tex[2].endian);
	e->tex[3].img = mlx_xpm_file_to_image(e->mlx, "textures/greystone.xpm",
			&x, &y);
	e->tex[3].data = mlx_get_data_addr(e->tex[3].img, &e->tex[3].bpp,
			&e->tex[3].s_l, &e->tex[3].endian);
	e->tex[4].img = mlx_xpm_file_to_image(e->mlx, "textures/colorstone.xpm",
			&x, &y);
	e->tex[4].data = mlx_get_data_addr(e->tex[4].img, &e->tex[4].bpp,
			&e->tex[4].s_l, &e->tex[4].endian);
}

void	ft_mlx(t_w3d *e)
{
	e->mlx = mlx_init();
	e->win = mlx_new_window(e->mlx, WIDTH, HEIGHT, "wolf3d");
	ft_tex_init(e);
	mlx_loop_hook(e->mlx, ft_draw, e);
	mlx_hook(e->win, 2, 0, ft_key_press, e);
	mlx_hook(e->win, 3, 0, ft_key_release, e);
	mlx_mouse_hide();
	mlx_mouse_move(e->win, WIDTH / 2, HEIGHT / 2);
	mlx_hook(e->win, 6, 0, ft_mouse_motion, e);
	mlx_hook(e->win, 17, 0, ft_close, e);
	mlx_loop(e->mlx);
}

int		ft_check_empty_file(t_w3d *e)
{
	char	*line;

	e->fd_tmp = open(e->file, O_RDONLY);
	if (get_next_line(e->fd_tmp, &line) <= 0)
	{
		close(e->fd_tmp);
		ft_putendl("error: file is invalid.");
		return (-1);
	}
	free(line);
	return (0);
}

int		main(int argc, char **argv)
{
	t_w3d	e;

	ft_bzero(&e, sizeof(t_w3d));
	if (argc != 2)
	{
		ft_putendl("usage: ./wolf3d <map>");
		return (-1);
	}
	e.file = argv[1];
	if (ft_check_empty_file(&e) == -1)
		return (-1);
	if (ft_check_file(&e) == -1 || ft_check_map(&e) == -1)
	{
		close(e.fd_tmp);
		return (-1);
	}
	close(e.fd_tmp);
	e.cam.dir.x = 1;
	e.cam.plane.y = 0.6;
	ft_mlx(&e);
	return (0);
}
