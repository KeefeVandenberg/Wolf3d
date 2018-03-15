/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvandenb <kvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 19:37:37 by kvandenb          #+#    #+#             */
/*   Updated: 2018/03/14 20:50:56 by kvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static t_ray *init_ray(void)
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
    e->planeY = 2 * (atan(0.50/1.0));
    return (e);
}

static t_env *init_env(void)
{
    t_env *e;

    if (!(e = malloc(sizeof(t_env))))
        exit(1);
    if (!(e->player = malloc(sizeof(t_player))))
        exit(1);
    if (!(e->t_mlx = malloc(sizeof(t_mlx))))
        exit(1);
    if ((e->t_mlx->mlx = mlx_init()) == NULL)
        exit(1);
    e->t_mlx->window = mlx_new_window(e->t_mlx->mlx, WIDTH, HEIGHT, "Wolf3d ~ kvandenb");
    e->t_mlx->image = mlx_new_image(e->t_mlx->mlx, WIDTH, HEIGHT);
    e->t_mlx->image_ptr = mlx_get_data_addr(e->t_mlx->image, &(e->t_mlx->bpp), &(e->t_mlx->sl), &(e->t_mlx->endian));
    e->ray = init_ray();
    e->player->x = 5;
    e->player->y = 5;
    e->ray->posX = e->player->x;
    e->ray->posY = e->player->y;
    return (e);
}

void    ft_exit(t_env *all)
{
    t_env *e;

    e = all;
    free(e->player);
    free(e->ray);
    free(e->t_mlx);
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
        if (e->map[(int)(e->ray->posY)][(int)(e->ray->posX + e->ray->dirX * 0.06)] == 0)
            e->ray->posX += e->ray->dirX * 0.06;
        if (e->map[(int)(e->ray->posY + e->ray->dirY * 0.06)][(int)e->ray->posX] == 0)
            e->ray->posY += e->ray->dirY * 0.06;
    }
    else if (keycode == 1)
    {
        if (e->map[(int)(e->ray->posY)][(int)(e->ray->posX - e->ray->dirX * 0.06)] == 0)
            e->ray->posX -= e->ray->dirX * 0.06;
        if (e->map[(int)(e->ray->posY - e->ray->dirY * 0.06)][(int)e->ray->posX] == 0)
            e->ray->posY -= e->ray->dirY * 0.06;
    }
    else if (keycode == 2)
    {
        e->ray->oldDirX = e->ray->dirX;
        e->ray->dirX = e->ray->dirX * cos(-.04) - e->ray->dirY * sin(-.04);
        e->ray->dirY = e->ray->oldDirX * sin(-.04) + e->ray->dirY * cos(-.04);
        e->ray->oldPlaneX = e->ray->planeX;
        e->ray->planeX = e->ray->planeX * cos(-.04) - e->ray->planeY * sin(-.04);
        e->ray->planeY = e->ray->oldPlaneX * sin(-0.04) + e->ray->planeY * cos(-.04);
    }
    else if (keycode == 0)
    {
        e->ray->oldDirX = e->ray->dirX;
        e->ray->dirX = e->ray->dirX * cos(0.04) - e->ray->dirY * sin(0.04);
        e->ray->dirY = e->ray->oldDirX * sin(0.04) + e->ray->dirY * cos(.04);
        e->ray->oldPlaneX = e->ray->planeX;
        e->ray->planeX = e->ray->planeX * cos(0.04) - e->ray->planeY * sin(0.04);
        e->ray->planeY = e->ray->oldPlaneX * sin(0.04) + e->ray->planeY * cos(0.04);
    }
    draw(e);
    return (0);
}


int ft_printmap(t_env *current)
{
    int y;
    int x;

    y = 0;
    while(y != HEIGHT_MAP)
    {
        x = 0;
        while (x != WIDTH_MAP)
        {
            printf("%d ", current->map[y][x]);
            x++;
        }
        printf("\n");
        y++;
    }
    return (0);
}

int main(int argc, char **argv)
{
    t_env *e;

    e = init_env();
    if (argc != 2)
    {
        exit(1);
    }   
    ft_initread(argv[1], e);
    ft_printmap(e);
    draw(e);
    mlx_hook(e->t_mlx->window, 2, 0, keydown, e);
    //mlx_hook(e->t_mlx->window, 17, 0, exit_hook, e);
    mlx_loop(e->t_mlx->mlx);
    return (0);
}
