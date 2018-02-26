/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvandenb <kvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 19:37:37 by kvandenb          #+#    #+#             */
/*   Updated: 2018/02/25 18:16:28 by kvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_mlx *mlxinit(void)
{
    t_mlx *e;
    
    e = malloc(sizeof(t_mlx));
    e->mlx = mlx_init();
    e->window = mlx_new_window(e->mlx, WIDTH, HEIGHT, "Wolf3d ~ kvandenb");
    e->image = mlx_new_image(e->mlx, WIDTH, HEIGHT);
    e->image_ptr = mlx_get_data_addr(e->image, &(e->bpp), &(e->sl), &(e->endian));
    return (e);
}
t_env *init_env(void)
{
    t_env *e;

    e = malloc(sizeof(t_env));
    e->player = malloc(sizeof(t_player));
    e->ray = malloc(sizeof(t_ray));
    e->mlx = malloc(sizeof(t_mlx));
    e->player->x = 0;
    e->player->y = 0;
    e->mlx = mlxinit();
    return (e);
}

int keydown(int keycode, t_env *all)
{
    printf("%d\n", keycode);
    if (keycode == 53)
        exit(1);
    return (0);
}

void    mlx_looper(t_env *all)
{
    t_env *e;

    e = all;
    mlx_hook(e->mlx->window, 2, 0, keydown, e);
    mlx_loop(e->mlx->mlx);
}

int main(int argc, char **argv)
{
    t_env *all;

    all = init_env();
    if (argc == 2)
    {
        ft_initread(argv[1], all);
        draw(all);
        mlx_looper(all);
    }
    return (0);
}