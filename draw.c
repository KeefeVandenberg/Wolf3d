/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvandenb <kvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 17:47:49 by kvandenb          #+#    #+#             */
/*   Updated: 2018/03/21 18:51:22 by kvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	pre_ray(t_ray *ray, int x)
{
	ray->cameraX = 2 * x / (double)(WIDTH) - 1;
	ray->rayDirX = ray->dirX + ray->planeX * ray->cameraX;
	ray->rayDirY = ray->dirY + ray->planeY * ray->cameraX;
	ray->mapX = (int)ray->posX;
	ray->mapY = (int)ray->posY;
	ray->deltaDistX = fabs(1 / ray->rayDirX);
	ray->deltaDistY = fabs(1 / ray->rayDirY);
	ray->hit = 0;
}

void	dir_ray(t_ray *ray)
{
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
}

void	hit_ray(t_env *current, t_ray *ray)
{
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
			ray->side = 1;
		}
		if (WIDTH_MAP <= ray->mapX || ray->mapX <= 0
			|| ray->mapY <= 0 || HEIGHT_MAP < ray->mapY)
		{
			ray->hit = 1;
			break ;
		}
		if (current->map[ray->mapY][ray->mapX] != 0)
			ray->hit = 1;
	}
}

void	draw_all(t_env *all)
{
	t_env	*current;
	t_ray	*ray;
	int		x;

	current = all;
	ray = current->ray;
	x = -1;
	while (x++ != WIDTH)
	{
		pre_ray(ray, x);
		dir_ray(ray);
		hit_ray(current, ray);
		ray->perpWallDist = ray->side == 0 ? (ray->mapX - ray->posX +
			(1 - ray->stepX) / 2) / ray->rayDirX : (ray->mapY -
			ray->posY + (1 - ray->stepY) / 2) / ray->rayDirY;
		ray->lineHeight = (int)(HEIGHT / ray->perpWallDist);
		ray->drawStart = -ray->lineHeight / 2 + HEIGHT / 2;
		if (ray->drawStart < 0)
			ray->drawStart = 0;
		ray->drawEnd = ray->lineHeight / 2 + HEIGHT / 2;
		if (ray->drawEnd >= HEIGHT)
			ray->drawEnd = HEIGHT - 1;
		color_picker(current);
		draw_vert(x, ray->drawStart, ray->drawEnd, current);
	}
}

int		draw(t_env *current)
{
	mlx_clear_window(current->t_mlx->mlx, current->t_mlx->window);
	ft_sky(current);
	draw_all(current);
	mini_map(current);
	mlx_put_image_to_window(current->t_mlx->mlx,
		current->t_mlx->window, current->t_mlx->image, 0, 0);
	return (1);
}
