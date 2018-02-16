/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvandenb <kvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 19:19:04 by kvandenb          #+#    #+#             */
/*   Updated: 2018/02/15 16:32:38 by kvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H
# define WIDTH 800
# define HEIGHT 800

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

typedef struct      s_read
{
    struct s_read          *next;
    struct s_read          *last;
    int             x;
    int             y;
    int             height;
}                   t_read;

#endif