/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvandenb <kvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 19:19:04 by kvandenb          #+#    #+#             */
/*   Updated: 2018/02/21 18:13:48 by kvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H
# define WIDTH 800
# define HEIGHT 800
# define EyeHeight 6

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

typedef struct      s_player
{
    double          x;
    double          y;
    double          viewangle;
}                   t_player;

typedef struct      s_env
{
    int             **map;
    int             x_max;
    int             y_max;
}                   t_env;

int                 ft_initread(char *str, t_env *all);
int                 ft_reopen(char *str, int y, t_env *all);
int                 ft_countnum(char *str);
int                 *parse(char *str, int x);

#endif