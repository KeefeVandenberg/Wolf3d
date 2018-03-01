/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvandenb <kvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/25 18:59:21 by kvandenb          #+#    #+#             */
/*   Updated: 2018/02/28 20:36:01 by kvandenb         ###   ########.fr       */
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
		hex = mlx_get_color_value(e->mlx->mlx, color);
		ft_memcpy(e->mlx->image_ptr + 4 * WIDTH * y + x * 4, &color, sizeof(int));
	}
}

void    draw_vert(int x, int start, int end, int color, t_env *all)
{
    printf("start = %d\nEnd = %d\n", start, end);
    if(start < end)
    {
        while(start != end)
        {
            pixel_put_img(all, x, start, color);
            start++;
        }
    }
    else
    {
        while(start != end)
        {
            pixel_put_img(all, x, start, color);
            start--;
        }
    }
}