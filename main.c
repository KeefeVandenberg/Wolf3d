/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvandenb <kvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 19:37:37 by kvandenb          #+#    #+#             */
/*   Updated: 2018/03/19 21:12:43 by kvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int keydown(int keycode, t_env *all)
{
    if (keycode == 53)
        ft_exit(all);
    if (keycode == 13)
        all->events->w = 1;
    if (keycode == 0)
        all->events->a = 1;
    if (keycode == 1)
        all->events->s = 1;
    if (keycode == 2)
        all->events->d = 1;
    keydown_after(all);
    return(0);
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

int exit_hook(t_env *e)
{
    ft_exit(e);
    return(0);
}

int key_unhook(int keycode, t_env *all)
{
    if (keycode == 13)
        all->events->w = 0;
    if (keycode == 0)
        all->events->a = 0;
    if (keycode == 1)
        all->events->s = 0;
    if (keycode == 2)
        all->events->d = 0;
    return (0);
}

int no_event(t_env *all)
{
    keydown_after(all);
    return (0);
}

int main(int argc, char **argv)
{
    t_env *e;

    if (argc != 2)
    {
        exit(1);
    }
    e = init_env();
    ft_initread(argv[1], e);
    ft_printmap(e);
    draw(e);
    mlx_hook(e->t_mlx->window, 2, 0, keydown, e);
    mlx_hook(e->t_mlx->window, 17, 0, exit_hook, e);
    mlx_hook(e->t_mlx->window, 3, 0, key_unhook, e);
    //mlx_expose_hook(e->t_mlx->mlx, no_event, e);
    mlx_loop(e->t_mlx->mlx);
    return (0);
}
