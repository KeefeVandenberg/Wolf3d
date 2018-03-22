/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvandenb <kvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 17:47:49 by kvandenb          #+#    #+#             */
/*   Updated: 2018/03/21 20:55:10 by kvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	pre_ray(t_ray *ray, int x)
{
	ray->camerax = 2 * x / (double)(WIDTH) - 1;
	ray->raydirx = ray->dirx + ray->planex * ray->camerax;
	ray->raydiry = ray->diry + ray->planey * ray->camerax;
	ray->mapx = (int)ray->posx;
	ray->mapy = (int)ray->posy;
	ray->deltadistx = fabs(1 / ray->raydirx);
	ray->deltadisty = fabs(1 / ray->raydiry);
	ray->hit = 0;
}

void	dir_ray(t_ray *ray)
{
	if (ray->raydirx < 0)
	{
		ray->stepx = -1;
		ray->sidedistx = (ray->posx - ray->mapx) * ray->deltadistx;
	}
	else
	{
		ray->stepx = 1;
		ray->sidedistx = (ray->mapx + 1.0 - ray->posx) * ray->deltadistx;
	}
	if (ray->raydiry < 0)
	{
		ray->stepy = -1;
		ray->sidedisty = (ray->posy - ray->mapy) * ray->deltadisty;
	}
	else
	{
		ray->stepy = 1;
		ray->sidedisty = (ray->mapy + 1.0 - ray->posy) * ray->deltadisty;
	}
}

void	hit_ray(t_env *current, t_ray *ray)
{
	while (ray->hit == 0)
	{
		if (ray->sidedistx < ray->sidedisty)
		{
			ray->sidedistx += ray->deltadistx;
			ray->mapx += ray->stepx;
			ray->side = 0;
		}
		else
		{
			ray->sidedisty += ray->deltadisty;
			ray->mapy += ray->stepy;
			ray->side = 1;
		}
		if (WIDTH_MAP <= ray->mapx || ray->mapx <= 0
			|| ray->mapy <= 0 || HEIGHT_MAP < ray->mapy)
		{
			ray->hit = 1;
			break ;
		}
		if (current->map[ray->mapy][ray->mapx] != 0)
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
		ray->perpwalldist = ray->side == 0 ? (ray->mapx - ray->posx +
			(1 - ray->stepx) / 2) / ray->raydirx : (ray->mapy -
			ray->posy + (1 - ray->stepy) / 2) / ray->raydiry;
		ray->lineheight = (int)(HEIGHT / ray->perpwalldist);
		ray->drawstart = -ray->lineheight / 2 + HEIGHT / 2;
		if (ray->drawstart < 0)
			ray->drawstart = 0;
		ray->drawend = ray->lineheight / 2 + HEIGHT / 2;
		if (ray->drawend >= HEIGHT)
			ray->drawend = HEIGHT - 1;
		color_picker(current);
		draw_vert(x, ray->drawstart, ray->drawend, current);
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
