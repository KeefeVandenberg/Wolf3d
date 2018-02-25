/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvandenb <kvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 17:47:49 by kvandenb          #+#    #+#             */
/*   Updated: 2018/02/25 15:40:50 by kvandenb         ###   ########.fr       */
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
    ray->deltaDistX = fabs(1 / ray->rayDirX);
    ray->deltaDistY = fabs(1 / ray->rayDirY);
    if (ray->rayDirX < 0)
    {
        ray->stepX = -1;
        ray->sideDistX = (ray->posX - (int)ray->posX) * ray->deltaDistX;
    }
    else
    {
        ray->stepX = 1;
        ray->sideDistX = ((int)ray->posX + 1.0 - ray->posX) * ray->deltaDisX;
    }
    if (ray->rayDirY < 0)
    {
        ray->stepY = -1;
        ray->sideDistY = (ray->posY - (int)ray->posY) * ray->deltaDistY;
    }
    else
    {
        ray->stepY = 1;
        ray->sideDistY = ((int)ray->posY + 1.0 - ray->posY) * ray->deltaDistY;
    }
}

void    ray_hit(t_env *current)
{
    t_ray *ray;

    ray = current->ray;
    while (!hit)
    {
        if (ray->sideDistX < ray->sideDistY)
        {
            ray->sideDistX += ray->deltaDistX;
            (int)ray->posX += ray->stepX;
            ray->side = 0;
        }
        else
        {
            ray->sideDistY += ray->deltaDistY;
            (int)ray->posY += ray->stepY;
            ray->side = 1;
        }
        if (current->map[(int)ray->posX][(int)ray->posY] > 0)
            ray->hit = 1;
    }
    if (ray->side == 0)
        ray->perpWallDist = ((int)ray->posX - ray->posX + (1 - ray->stepX) / 2) / ray->rayDirX;
    else
        ray->perpWallDist = ((int)ray->posY - ray->posY + (1 - ray->stepY) / 2) / ray->rayDirY;
}

void    draw_line(t_env *all)
{
    t_env *current;
    int lineheight;

    current = all;
    lineheight = (int)(HEIGHT / current->ray->perpWallDist);
    
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
    current->ray->hit = 0;
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
        ray_hit(current);
        draw_line(current);
    }
}