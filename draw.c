/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvandenb <kvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 17:47:49 by kvandenb          #+#    #+#             */
/*   Updated: 2018/02/27 18:05:34 by kvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void draw_all(t_env *all)
{
    t_env *current;
    t_ray *ray;
    int x;

    current = all;
    ray = malloc(sizeof(t_ray));
    ray->posX = 5;
    ray->posY = 5;
    ray->dirX = -1.0;
    ray->dirY = 0.0;
    ray->planeX = 0;
    ray->planeY = .66;
    x = -1;
    while (x++ != WIDTH)
    {
        ray->cameraX = 2 * x / (double)(WIDTH) - 1;
        ray->rayDirX = ray->dirX + ray->planeX * ray->cameraX;
        ray->rayDirY = ray->dirY + ray->planeY * ray->cameraX;
        ray->mapX = (int)ray->posX;
        ray->mapY = (int)ray->posY;
        ray->deltaDistX = fabs(1 / ray->rayDirX);
        ray->deltaDistY = fabs(1 / ray->rayDirY);
        ray->hit = 0;
        if (ray->rayDirX < 0)
        {
            ray->stepX = -1;
            ray->sideDistX = (ray->posX - ray->mapX) * ray->deltaDistX;
        }
        else
        {
            ray->stepX = 1;
            ray->sideDistX = (ray->mapX + 1.0 - ray->posX) * ray->deltaDistX;
        }
        if (ray->rayDirY < 0)
        {
            ray->stepY = -1;
            ray->sideDistY = (ray->posY - ray->mapY) * ray->deltaDistY;
        }
        else
        {
            ray->stepY = 1;
            ray->sideDistY = (ray->mapY + 1.0 - ray->posY) * ray->deltaDistY;
        }
        while (ray->hit == 0)
        {
            if (ray->sideDistX < ray->sideDistY)
            {
                ray->sideDistX += ray->deltaDistX;
                ray->mapX += ray->stepX;
                ray->side = 0;
            }
            else
            {
                ray->sideDistY += ray->deltaDistY;
                ray->mapY += ray->stepY;
                ray->side = 0;
            }
            if (current->map[ray->mapX][ray->mapY] > 0)
                ray->hit = 1;
        }
        if (ray->side == 0)
            ray->perpWallDist = (ray->mapX - ray->posX + (1 - ray->stepX) / 2) / ray->rayDirX;
        else
            ray->perpWallDist = (ray->mapY - ray->posY + (1 - ray->stepY) / 2) / ray->rayDirY;
        printf("mapY = %d posY = %f stepy = %d rayDirY = %f\n", ray->mapY, ray->posY, ray->stepY, ray->rayDirY);
        ray->lineHeight = (int)(HEIGHT / ray->perpWallDist);
        ray->drawStart = -ray->lineHeight / 2 + HEIGHT / 2;
        if (ray->drawStart < 0)
            ray->drawStart = 0;
        ray->drawEnd = ray->lineHeight / 2 + HEIGHT / 2;
        if (ray->drawEnd >= HEIGHT)
            ray->drawEnd = HEIGHT - 1;
        ray->color = ROOF;
        if (ray->side == 1)
            ray->color = ray->color / 2;
        draw_vert(x, ray->drawStart, ray->drawEnd, ray->color, current);
    }
}

int draw(t_env *all)
{
    t_env *current;
    int x_tmp;

    x_tmp = 1;
    current = all;
    draw_all(current);
    mlx_clear_window(current->mlx->mlx, current->mlx->window);
    mlx_put_image_to_window(current->mlx->mlx, current->mlx->window, current->mlx->image, 0, 0);
    return (1);
}