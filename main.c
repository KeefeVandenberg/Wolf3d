/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvandenb <kvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 19:37:37 by kvandenb          #+#    #+#             */
/*   Updated: 2018/02/28 21:06:18 by kvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_ray *init_ray(void)
{
    t_ray *e;

    if (!(e = malloc(sizeof(t_ray))))
    {
        ft_putendl("Ray wasn't initated correctly");
        exit(1);
    }
    e->dirX = -1.0;
    e->dirY = 0.0;
    e->planeX = 0;
    e->planeY = 2 * (atan(0.90/1.0));
    return (e);
}

t_env *init_env(void)
{
    t_env *e;

    if (!(e = malloc(sizeof(t_env))))
        exit(1);
    if (!(e->player = malloc(sizeof(t_player))))
        exit(1);
    if (!(e->mlx = malloc(sizeof(t_mlx))))
        exit(1);
    e->ray = init_ray();
    e->player->x = 5;
    e->player->y = 5;
    e->ray->posX = e->player->x;
    e->ray->posY = e->player->y;
    return (e);
}

void    ft_freemap(t_env *e)
{
    int index;
    t_env *current;
    int *i;

    index = 0;
    current = e;
    while(index != current->y_max)
    {
        i = current->map[index];
        free(i);
        index++;
    }
    free(current->map);
}

void    ft_exit(t_env *all)
{
    t_env *e;

    e = all;
    free(e->player);
    free(e->ray);
    free(e->mlx);
    free(e->map);
    free(e);
    exit(1);
}

int keydown(int keycode, t_env *all)
{
    t_env *e;

    e = all;
    printf("%d\n", keycode);
    if (keycode == 53)
        exit(1);
    if (keycode == 13)
    {
        if (e->map[(int)(e->ray->posX + e->ray->dirX * 0.06)][(int)(e->ray->posY)] == 0)
            e->ray->posX += e->ray->dirX * 0.06;
        if (e->map[(int)e->ray->posX][(int)(e->ray->posY + e->ray->dirY * 0.06)] == 0)
            e->ray->posY += e->ray->dirY * 0.06;
    }
    else if (keycode == 1)
    {
        if (e->map[(int)(e->ray->posX - e->ray->dirX * 0.06)][(int)(e->ray->posY)] == 0)
            e->ray->posX -= e->ray->dirX * 0.06;
        if (e->map[(int)e->ray->posX][(int)(e->ray->posY - e->ray->dirY * 0.06)] == 0)
            e->ray->posY -= e->ray->dirY * 0.06;
    }
    else if (keycode == 0)
    {
        e->ray->oldDirX = e->ray->dirX;
        e->ray->dirX = e->ray->dirX * cos(-.04) - e->ray->dirY * sin(-.04);
        e->ray->dirY = e->ray->oldDirX * sin(-.04) + e->ray->dirY * cos(-.04);
        e->ray->oldPlaneX = e->ray->planeX;
        e->ray->planeX = e->ray->planeX * cos(-.04) - e->ray->planeY * sin(-.04);
        e->ray->planeY = e->ray->oldPlaneX * sin(-0.04) + e->ray->planeY * cos(-.04);
    }
    draw(e);
    return (0);
}

void    init(t_env *e)
{
    if ((e->mlx->mlx = mlx_init()) == NULL || (e->mlx->window = mlx_new_window(e->mlx->mlx, WIDTH, HEIGHT, "Wolf3d ~ kvandenb")) == NULL)
        exit(1);
    if ((e->mlx->image = mlx_new_image(e->mlx->mlx, WIDTH, HEIGHT)) == NULL)
        exit(1);
    e->mlx->image_ptr = mlx_get_data_addr(e->mlx->image, &(e->mlx->bpp), &(e->mlx->sl), &(e->mlx->endian));
}

int main(int argc, char **argv)
{
    t_env *e;

    e = init_env();
    init(e);
    if (argc != 2)
    {
        exit(1);
    }   
    ft_initread(argv[1], e);
    draw(e);
    printf("finished drawing\n");
    mlx_hook(e->mlx->window, 2, 0, keydown, e);
    mlx_loop(e->mlx->mlx);
    return (0);
}