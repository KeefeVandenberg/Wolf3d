/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvandenb <kvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 17:41:51 by kvandenb          #+#    #+#             */
/*   Updated: 2018/03/19 21:12:05 by kvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		ft_exit(t_env *e)
{
	int i;

	i = 0;
	free(e->player);
	free(e->ray);
	free(e->t_mlx);
	free(e->events);
	while (i != HEIGHT_MAP)
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
	e->dirX = -1.0;
	e->dirY = 0.0;
	e->planeX = 0;
	e->planeY = 2 * (atan(.45/1.0));
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
	if (!(e->t_mlx = malloc(sizeof(t_mlx))))
		ft_exit(e);
	if ((e->t_mlx->mlx = mlx_init()) == NULL)
		ft_exit(e);
	e->t_mlx->window = mlx_new_window(e->t_mlx->mlx, WIDTH, HEIGHT, "Wolf3d ~ kvandenb");
	e->t_mlx->image = mlx_new_image(e->t_mlx->mlx, WIDTH, HEIGHT);
	e->t_mlx->image_ptr = mlx_get_data_addr(e->t_mlx->image, &(e->t_mlx->bpp), &(e->t_mlx->sl), &(e->t_mlx->endian));
	e->ray = init_ray();
	e->events = init_events();
	e->player->x = 5;
	e->player->y = 5;
	e->ray->posX = e->player->x;
	e->ray->posY = e->player->y;
	return (e);
}