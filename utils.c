/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvandenb <kvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/25 18:59:21 by kvandenb          #+#    #+#             */
/*   Updated: 2018/03/21 18:47:04 by kvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		ft_checkcharacters(char *buf)
{
	int i;

	i = 0;
	while (buf[i])
	{
		if (!(buf[i] == ' ' || ft_isdigit(buf[i]) || buf[i] == '\n'))
			return (0);
		i++;
	}
	return (1);
}

void	pixel_put_img(t_env *j, int x, int y, int color)
{
	t_env	*e;
	int		hex;

	e = j;
	if (y < 0)
		y = 0;
	if (x < 0)
		x = 0;
	if (x < WIDTH && y < HEIGHT)
	{
		hex = mlx_get_color_value(e->t_mlx->mlx, color);
		ft_memcpy(e->t_mlx->image_ptr + 4 * WIDTH * y + x * 4,
			&color, sizeof(int));
	}
}

void	draw_vert(int x, int start, int end, t_env *all)
{
	if (start < end)
	{
		while (start != end)
		{
			pixel_put_img(all, x, start, all->ray->color);
			start++;
		}
	}
	else
	{
		while (start != end)
		{
			pixel_put_img(all, x, start, all->ray->color);
			start--;
		}
	}
}

void	ft_sky(t_env *all)
{
	int		x;
	int		roof;
	int		y;
	int		ground;
	t_env	*current;

	ground = FLOOR;
	roof = ROOF;
	x = 0;
	current = all;
	while (x != WIDTH)
	{
		current->ray->color = ground;
		draw_vert(x, HEIGHT / 2, HEIGHT, current);
		current->ray->color = roof;
		draw_vert(x, 0, HEIGHT / 2, current);
		x++;
	}
}

int		color_picker(t_env *current)
{
	t_ray	*ray;
	int		i;

	ray = current->ray;
	i = current->map[ray->mapY][ray->mapX];
	if (i > 5)
		i = i % 5;
	if (i == 1)
		ray->color = ray->side == 1 ? PURPLE : PURPLE2;
	else if (i == 2)
		ray->color = ray->side == 1 ? ORANGE : ORANGE2;
	else if (i == 3)
		ray->color = ray->side == 1 ? GREEN2 : GREEN;
	else if (i == 4)
		ray->color = ray->side == 1 ? BLUE : BLUE2;
	else if (i == 5)
		ray->color = ray->side == 1 ? PURPLE : PURPLE2;
	i = 0;
	return (0);
}
