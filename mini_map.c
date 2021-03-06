/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvandenb <kvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 17:26:57 by kvandenb          #+#    #+#             */
/*   Updated: 2018/03/21 20:51:40 by kvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	draw_cube(int x, int y, t_env *all)
{
	int px;
	int py;

	px = x * 5;
	py = y * 5;
	while (px != (x * 5) + 5)
	{
		all->ray->color = 0x4C4C4C;
		draw_vert(px, py, py + 5, all);
		px++;
	}
}

void	ft_drawplayer(t_env *current)
{
	int i;

	i = 0;
	while (i != 3)
	{
		current->ray->color = 0xFF0000;
		draw_vert(((current->ray->posx + 1) * 5) + i, (current->ray->posy + 1)
			* 5, ((current->ray->posy + 1) * 5) + 3, current);
		i++;
	}
}

void	mini_map(t_env *current)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (y != HEIGHT_MAP)
	{
		x = 0;
		while (x != WIDTH_MAP)
		{
			if (current->map[y][x] >= 1)
			{
				draw_cube(x + 1, y + 1, current);
			}
			x++;
		}
		y++;
	}
	ft_drawplayer(current);
}
