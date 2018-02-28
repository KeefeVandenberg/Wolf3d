/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvandenb <kvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 19:19:04 by kvandenb          #+#    #+#             */
/*   Updated: 2018/02/27 18:05:55 by kvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H
# define WIDTH 800
# define HEIGHT 800
# define EyeHeight 6
# define FLOOR 0xCCCCCC //grey
# define ROOF 0x7b7FFF //light blue
# define NORTH 0xFF7B7B // pinkish
# define WEST 0x7BFF7F // light green
# define SOUTH 0xBD7BFF // light purple
# define EAST 0x000b7E // deep blue
# define distance(x1, y1, x2, y2) sqrt((pow(x2 - x1, 2)) + (pow(y2 - y1, 2)))

# include <time.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include "minilibx_macos/mlx.h"
# include "GNL/libft/libft.h"
# include "GNL/get_next_line.h"
# include <stdlib.h>
# include <fcntl.h>
# include "math.h"

typedef struct      s_mlx
{
    void            *mlx;
    void            *image;
    void            *image_ptr;
    void            *window;
    int             endian;
    int             sl;
    int             bpp;
}                   t_mlx;

typedef struct      s_player
{
    double          x;
    double          y;
    double          viewangle;
}                   t_player;

typedef struct      s_ray
{
    double          planeX;
    double          planeY;
    double          posX;
    double          posY;
    int             mapX;
    int             mapY;
    double          sideDistX;
    double          sideDistY;
    double          dirX;
    double          dirY;
    double          cameraX;
    double          rayDirX;
    double          rayDirY;
    double          deltaDistX;
    double          deltaDistY;
    double          perpWallDist;
    int             stepX;
    int             stepY;
    int             side;
    int             hit;
    double          time;
    double          oldTime;
    int             lineHeight;
    int             drawStart;
    int             drawEnd;
    int             color;
}                   t_ray;

typedef struct      s_env
{
    t_player        *player;
    t_ray           *ray;
    t_mlx           *mlx;
    int             **map;
    int             x_max;
    int             y_max;    
}                   t_env;

int                 ft_initread(char *str, t_env *all);
int                 ft_reopen(char *str, int y, t_env *all);
int                 ft_countnum(char *str);
int                 *parse(char *str, int x);
int                 draw(t_env *all); 
void                draw_vert(int x, int start, int end, int color, t_env *all);
void                ft_exit(t_env *all);

#endif