/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvandenb <kvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 19:19:04 by kvandenb          #+#    #+#             */
/*   Updated: 2018/03/21 20:56:37 by kvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H
# define WIDTH 800
# define HEIGHT 800
# define HEIGHT_MAP 18
# define WIDTH_MAP 18
# define FLOOR 0xCCCCCC
# define ROOF 0x7b7FFF
# define RED 0xff5050
# define RED2 0xff5252
# define ORANGE 0xffa852
# define ORANGE2 0xff7d52
# define GREEN 0x009900
# define GREEN2 0x33cc33
# define BLUE 0x3380cc
# define BLUE2 0x3333cc
# define PURPLE 0x8033cc
# define PURPLE2 0xa633cc

# include <time.h>
# include <stdio.h>
# include <unistd.h>
# include "minilibx_macos/mlx.h"
# include "GNL/libft/libft.h"
# include "GNL/get_next_line.h"
# include <stdlib.h>
# include <fcntl.h>
# include "math.h"

typedef struct		s_mls
{
	void			*mlx;
	void			*image;
	void			*image_ptr;
	void			*window;
	int				endian;
	int				sl;
	int				bpp;
}					t_mls;

typedef struct		s_player
{
	int				x;
	int				y;
	double			viewangle;
}					t_player;

typedef struct		s_ray
{
	double			planex;
	double			planey;
	double			posx;
	double			posy;
	int				mapx;
	int				mapy;
	double			sidedistx;
	double			sidedisty;
	double			dirx;
	double			diry;
	double			olddirx;
	double			oldplanex;
	double			camerax;
	double			raydirx;
	double			raydiry;
	double			deltadistx;
	double			deltadisty;
	double			perpwalldist;
	int				stepx;
	int				stepy;
	int				side;
	int				hit;
	double			time;
	double			oldtime;
	int				lineheight;
	int				drawstart;
	int				drawend;
	int				color;
	double			frametime;
}					t_ray;

typedef struct		s_events
{
	int				w;
	int				a;
	int				s;
	int				d;
	int				crouch_offset;
}					t_events;

typedef struct		s_env
{
	t_player		*player;
	t_ray			*ray;
	t_mls			*t_mlx;
	t_events		*events;
	int				**map;
	int				bytes_read;
}					t_env;

int					keydown_after(t_env *all);
t_env				*init_env(void);
void				mini_map(t_env *current);
int					draw(t_env *current);
void				ft_exit(t_env *e);
int					keydown_after(t_env *all);
void				draw_vert(int x, int start, int end, t_env *all);
int					ft_initread(char *str, t_env *all);
int					color_picker(t_env *current);
void				ft_sky(t_env *all);
int					ft_checkcharacters(char *buf);
int					check_map(t_env *e);

#endif
