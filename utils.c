/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvandenb <kvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/25 18:59:21 by kvandenb          #+#    #+#             */
/*   Updated: 2018/03/20 14:18:31 by kvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		pixel_put_img(t_env *j, int x, int y, int color)
{
	t_env	*e;
	int		hex;

	e = j;
	if (x < WIDTH && y < HEIGHT)
	{
		hex = mlx_get_color_value(e->t_mlx->mlx, color);
		ft_memcpy(e->t_mlx->image_ptr + 4 * WIDTH * y + x * 4,
			&color, sizeof(int));
	}
}

void		draw_vert(int x, int start, int end, t_env *all)
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
