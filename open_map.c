/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvandenb <kvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 17:21:48 by kvandenb          #+#    #+#             */
/*   Updated: 2018/02/28 19:26:24 by kvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int *parse(char *str, int x)
{
    int *intarr;
    int i;
    int i_int;

    i = 0;
    i_int = 0;
    if(!(intarr = (int *)malloc(sizeof(int) * x)))
    {
        ft_putendl("Single array failed to malloc");
        exit(1);
    }
    while (str[i] && i_int != x + 1)
    {
        if(ft_isdigit(str[i]))
        {
            intarr[i_int] = ft_atoi(str);
            i_int++;
        }
        str++;
    }
    return (intarr);
}

int ft_countnum(char *str)
{
    int i;
    int x;

    i = 0;
    x = 0;
    while(str[i])
    {
        if (ft_isdigit(str[i]))
            x++;
        i++;
    }
    return (x);
}

int ft_reopen(char *str, int y, t_env *all)
{
    int fd;
    t_env *current;
    char *line;
    int index;
    int x;

    fd = open(str, O_RDONLY);
    current = all;
    line = 0;
    index = 0;
    if(!(current->map = (int **)malloc(sizeof(int) * y)))
    {
        ft_putendl("Map failed to malloc");
        exit(1);
    }
    while (get_next_line(fd, &line) != 0)
    {
        x = ft_countnum(line);
        current->map[index] = parse(line, x);
        line = NULL;
        index++;
    }
    current->map[index] = NULL;
    current->x_max = x;
    close(fd);
    return (0);
}

int ft_initread(char *str, t_env *all)
{
    t_env *current;
    int fd;
    char *line;
    int y;
    int x;

    y = 0;
    line = NULL;
    current = all;
    fd = open(str, O_RDONLY);
    while (get_next_line(fd, &line) != 0)
    {
        line = 0;
        y++;
    }
    current->y_max = y;
    close(fd);
    ft_reopen(str, y, current);
    return (0);
}