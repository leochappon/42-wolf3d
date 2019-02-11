/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchappon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 16:00:11 by lchappon          #+#    #+#             */
/*   Updated: 2019/02/11 18:16:51 by lchappon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include "../libft/includes/libft.h"
# include <../minilibx/mlx.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <pthread.h>

# define WIDTH 800
# define HEIGHT 640
# define TEX_W 64
# define TEX_H 64

typedef struct		s_intxy
{
	int				x;
	int				y;
}					t_intxy;

typedef struct		s_doublexy
{
	double			x;
	double			y;
}					t_doublexy;

typedef struct		s_img
{
	void			*img;
	char			*data;
	int				bpp;
	int				s_l;
	int				endian;
}					t_img;

typedef struct		s_player
{
	t_doublexy		pos;
	t_doublexy		dir;
	t_doublexy		plane;
}					t_player;

typedef struct		s_ray
{
	t_doublexy		dir;
	t_intxy			pos;
	t_intxy			move;
	t_doublexy		cast;
	t_doublexy		casting;
}					t_ray;

typedef struct		s_wall
{
	int				side;
	double			dist;
	int				height;
	int				size;
	int				top;
	int				bottom;
	double			hit;
	t_intxy			tex;
}					t_wall;

typedef struct		s_floor
{
	t_doublexy		wall;
	double			dist;
	double			weight;
	t_doublexy		tile;
	t_intxy			tex;
}					t_floor;

typedef struct		s_move
{
	int				forward;
	int				backward;
	int				right;
	int				left;
	int				up;
	int				up2;
	int				fly;
	int				down;
	int				sprint;
	float			speed;
	float			v;
}					t_move;

typedef struct		s_rot
{
	int				up;
	int				down;
	int				right;
	int				left;
	double			speed;
	double			v;
}					t_rot;

typedef struct		s_w3d
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*data;
	int				bpp;
	int				s_l;
	int				endian;
	char			*file;
	int				fd;
	int				fd_tmp;
	int				**map;
	t_intxy			size;
	int				x;
	int				xx;
	int				y;
	double			screen;
	t_player		cam;
	t_ray			ray;
	int				num;
	t_img			tex[9];
	t_wall			wall;
	t_floor			floor;
	t_move			move;
	t_rot			rot;
	int				info;
	int				mouse;
}					t_w3d;

int					ft_close(t_w3d *e);

int					ft_check_file(t_w3d *e);

void				ft_get_pos(t_w3d *e, int x, int y);
int					ft_check_map(t_w3d *e);
void				ft_free_map(t_w3d *e);

int					ft_draw(t_w3d *e);

void				ft_raycasting_init(t_w3d *e);
void				ft_raycasting(t_w3d *e);
void				ft_wallcasting(t_w3d *e);
void				ft_floorcasting(t_w3d *e);

void				ft_walls(t_w3d *e);
void				ft_floor(t_w3d *e);
void				ft_ceiling(t_w3d *e);

int					ft_key_press(int keycode, t_w3d *e);
int					ft_key_release(int keycode, t_w3d *e);
int					ft_mouse_motion(int x, int y, t_w3d *e);

void				ft_move(t_w3d *e);
void				ft_rotate(t_w3d *e);

#endif
