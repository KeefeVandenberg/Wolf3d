/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvandenb <kvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 17:35:52 by kvandenb          #+#    #+#             */
/*   Updated: 2018/03/21 18:09:53 by kvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	left(t_env *e)
{
	if (e->events->a == 1)
	{
		e->ray->oldDirX = e->ray->dirX;
		e->ray->dirX = e->ray->dirX * cos(0.04) - e->ray->dirY * sin(0.04);
		e->ray->dirY = e->ray->oldDirX * sin(0.04) + e->ray->dirY * cos(.04);
		e->ray->oldPlaneX = e->ray->planeX;
		e->ray->planeX = e->ray->planeX
			* cos(0.04) - e->ray->planeY * sin(0.04);
		e->ray->planeY = e->ray->oldPlaneX
			* sin(0.04) + e->ray->planeY * cos(0.04);
	}
}

void	right(t_env *e)
{
	if (e->events->d == 1)
	{
		e->ray->oldDirX = e->ray->dirX;
		e->ray->dirX = e->ray->dirX * cos(-.04) - e->ray->dirY * sin(-.04);
		e->ray->dirY = e->ray->oldDirX * sin(-.04) + e->ray->dirY * cos(-.04);
		e->ray->oldPlaneX = e->ray->planeX;
		e->ray->planeX = e->ray->planeX
			* cos(-.04) - e->ray->planeY * sin(-.04);
		e->ray->planeY = e->ray->oldPlaneX
			* sin(-0.04) + e->ray->planeY * cos(-.04);
	}
}

void	back(t_env *e)
{
	if (e->events->s == 1)
	{
		if (e->map[(int)(e->ray->posY)]
			[(int)(e->ray->posX - e->ray->dirX * 0.06)] == 0)
			e->ray->posX -= e->ray->dirX * 0.06;
		if (e->map[(int)(e->ray->posY - e->ray->dirY * 0.06)]
			[(int)e->ray->posX] == 0)
			e->ray->posY -= e->ray->dirY * 0.06;
	}
}

void	foward(t_env *e)
{
	if (e->events->w == 1)
	{
		if (e->map[(int)(e->ray->posY)]
			[(int)(e->ray->posX + e->ray->dirX * 0.06)] == 0)
			e->ray->posX += e->ray->dirX * 0.06;
		if (e->map[(int)(e->ray->posY + e->ray->dirY * 0.06)]
			[(int)e->ray->posX] == 0)
			e->ray->posY += e->ray->dirY * 0.06;
	}
}

int		keydown_after(t_env *all)
{
	t_env *e;

	e = all;
	left(e);
	right(e);
	foward(e);
	back(e);
	draw(e);
	return (0);
}
