/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvandenb <kvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 17:41:51 by kvandenb          #+#    #+#             */
/*   Updated: 2018/03/21 20:55:49 by kvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int			check_map(t_env *e)
{
	if (e->map[4][4] != 0 || e->map[5][4] != 0
		|| e->map[4][5] != 0 || e->map[5][5] != 0)
	{
		ft_putendl("Error : not enough free spaces around starting area");
		ft_exit(e);
	}
	return (0);
}

void		ft_exit(t_env *e)
{
	int i;

	i = 0;
	free(e->player);
	free(e->ray);
	free(e->t_mlx);
	free(e->events);
	while (i != HEIGHT_MAP - 1)
		free(e->map[i++]);
	free(e->map);
	free(e);
	exit(1);
}

t_ray		*init_ray(void)
{
	t_ray *e;

	if (!(e = malloc(sizeof(t_ray))))
		return (NULL);
	e->dirx = -1.0;
	e->diry = 0.0;
	e->planex = 0;
	e->planey = 2 * (atan(.45 / 1.0));
	return (e);
}

t_events	*init_events(void)
{
	t_events *e;

	e = malloc(sizeof(t_events));
	e->w = 0;
	e->a = 0;
	e->s = 0;
	e->d = 0;
	return (e);
}

t_env		*init_env(void)
{
	t_env *e;

	if (!(e = malloc(sizeof(t_env))))
		ft_exit(e);
	if (!(e->player = malloc(sizeof(t_player))))
		ft_exit(e);
	if (!(e->t_mlx = malloc(sizeof(t_mls))))
		ft_exit(e);
	if ((e->t_mlx->mlx = mlx_init()) == NULL)
		ft_exit(e);
	e->t_mlx->window = mlx_new_window(e->t_mlx->mlx,
		WIDTH, HEIGHT, "Wolf3d ~ kvandenb");
	e->t_mlx->image = mlx_new_image(e->t_mlx->mlx, WIDTH, HEIGHT);
	e->t_mlx->image_ptr = mlx_get_data_addr(e->t_mlx->image,
		&(e->t_mlx->bpp), &(e->t_mlx->sl), &(e->t_mlx->endian));
	e->ray = init_ray();
	e->events = init_events();
	e->player->x = 5;
	e->player->y = 5;
	e->ray->posx = e->player->x;
	e->ray->posy = e->player->y;
	return (e);
}
