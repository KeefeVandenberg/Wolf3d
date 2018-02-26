/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvandenb <kvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 17:47:49 by kvandenb          #+#    #+#             */
/*   Updated: 2018/02/25 20:07:16 by kvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*scratch what I was doing with the casting the pos x it is messing up the value
// tomorrow I will stop being lazy and create the mapx and mapy for the functions
// I am going to call it a night 8:07 pm
*/


void    calc_ray(t_ray *all, int x)
{
    t_ray *ray;

    ray = all;
    ray->cameraX = 2 * x / (double)WIDTH - 1;
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
        ray->sideDistX = ((int)ray->posX + 1.0 - ray->posX) * ray->deltaDistX;
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

void    ray_hit(t_env *all)
{
    t_ray *ray;
    t_env *current;

    current = all;
    ray = all->ray;
    while (!ray->hit)
    {
        if (ray->sideDistX < ray->sideDistY)
        {
            ray->sideDistX += ray->deltaDistX;
            ray->posX = ray->stepX + (int)ray->posX;
            ray->side = 0;
        }
        else
        {
            ray->sideDistY += ray->deltaDistY;
            ray->posY = ray->stepY + (int)ray->posY;
            ray->side = 1;
        }
        printf("posX = %f\nposY = %f\n\n", ray->posX, ray->posY);
        if (current->map[(int)ray->posX][(int)ray->posY] > 0)
            ray->hit = 1;
    }
    if (ray->side == 0)
        ray->perpWallDist = ((int)ray->posX - ray->posX + (1 - ray->stepX) / 2) / ray->rayDirX;
    else
        ray->perpWallDist = ((int)ray->posY - ray->posY + (1 - ray->stepY) / 2) / ray->rayDirY;
}

void    draw_line(t_env *all, int x)
{
    t_env *current;
    int lineHeight;
    int drawStart;
    int drawEnd;
    int color;

    current = all;
    lineHeight = (int)(HEIGHT / current->ray->perpWallDist);
    drawStart = -lineHeight / 2 + HEIGHT / 2;
    drawEnd = lineHeight / 2 + HEIGHT / 2;
    if (drawStart < 0)
        drawStart = 0;
    if (drawEnd >= HEIGHT)
        drawEnd = HEIGHT - 1;
    if (current->map[(int)current->ray->posX][(int)current->ray->posX] == 1)
        color = ROOF;
    if (current->ray->side == 1)
    {
        color = color / 2;
    }
    draw_vert(x, drawStart, drawEnd, color, current);
}

void    reinit_ray(t_env *all)
{
    t_env *current;

    current = all;
    current->ray->posX = 2; //current->player->x;
    current->ray->posY = 2; //current->player->y;
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
        calc_ray(current->ray, x_tmp);
        ray_hit(current);
        draw_line(current, x_tmp);
        x_tmp++;
    }
    mlx_clear_window(current->mlx->mlx, current->mlx->window);
    mlx_put_image_to_window(current->mlx->mlx, current->mlx->window, current->mlx->image, 0, 0);
    return (1);
}