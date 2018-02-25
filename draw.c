/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvandenb <kvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 17:47:49 by kvandenb          #+#    #+#             */
/*   Updated: 2018/02/25 14:49:43 by kvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void    calc_ray(t_ray *all, int x)
{
    t_ray *ray;

    ray = all;
    ray->cameraX = 2 * x / double(WIDTH) - 1;
    ray->rayDirX = ray->dirX + ray->planeX * ray->cameraX;
    ray->rayDirY = ray->dirY + ray->planeY * ray->cameraX;
    
}

void    reinit_ray(t_env *all)
{
    t_env *current;

    current = all;
    current->ray->posX = current->player->x;
    current->ray->posY = current->player->y;
    current->ray->dirX = -1;
    current->ray->dirY = 0;
    current->ray->planeX = 0;
    current->ray->planeY = 0.66;
}

int draw(t_env *all)
{
    t_env *current;
    int x_tmp;

    x_tmp = 0;
    current = all;
    reinit_ray(current);
    while (x_tmp != WIDTH)
    {
        calc_ray(current->ray, x);
    }
}