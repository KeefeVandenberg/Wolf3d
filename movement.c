/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvandenb <kvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 17:35:52 by kvandenb          #+#    #+#             */
/*   Updated: 2018/03/21 20:53:20 by kvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	left(t_env *e)
{
	if (e->events->a == 1)
	{
		e->ray->olddirx = e->ray->dirx;
		e->ray->dirx = e->ray->dirx * cos(0.04) - e->ray->diry * sin(0.04);
		e->ray->diry = e->ray->olddirx * sin(0.04) + e->ray->diry * cos(.04);
		e->ray->oldplanex = e->ray->planex;
		e->ray->planex = e->ray->planex
			* cos(0.04) - e->ray->planey * sin(0.04);
		e->ray->planey = e->ray->oldplanex
			* sin(0.04) + e->ray->planey * cos(0.04);
	}
}

void	right(t_env *e)
{
	if (e->events->d == 1)
	{
		e->ray->olddirx = e->ray->dirx;
		e->ray->dirx = e->ray->dirx * cos(-.04) - e->ray->diry * sin(-.04);
		e->ray->diry = e->ray->olddirx * sin(-.04) + e->ray->diry * cos(-.04);
		e->ray->oldplanex = e->ray->planex;
		e->ray->planex = e->ray->planex
			* cos(-.04) - e->ray->planey * sin(-.04);
		e->ray->planey = e->ray->oldplanex
			* sin(-0.04) + e->ray->planey * cos(-.04);
	}
}

void	back(t_env *e)
{
	if (e->events->s == 1)
	{
		if (e->map[(int)(e->ray->posy)]
			[(int)(e->ray->posx - e->ray->dirx * 0.06)] == 0)
			e->ray->posx -= e->ray->dirx * 0.06;
		if (e->map[(int)(e->ray->posy - e->ray->diry * 0.06)]
			[(int)e->ray->posx] == 0)
			e->ray->posy -= e->ray->diry * 0.06;
	}
}

void	foward(t_env *e)
{
	if (e->events->w == 1)
	{
		if (e->map[(int)(e->ray->posy)]
			[(int)(e->ray->posx + e->ray->dirx * 0.06)] == 0)
			e->ray->posx += e->ray->dirx * 0.06;
		if (e->map[(int)(e->ray->posy + e->ray->diry * 0.06)]
			[(int)e->ray->posx] == 0)
			e->ray->posy += e->ray->diry * 0.06;
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
