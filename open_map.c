/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvandenb <kvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 17:21:48 by kvandenb          #+#    #+#             */
/*   Updated: 2018/03/15 18:43:58 by kvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"


int *parse(char *str, int x)
{
    int *arr;
    int i;
    int k;

    i = 0;
    k = 0;
    arr = (int *)malloc(sizeof(int) * x);
    while (*str)
    {
        if (ft_isdigit(*str) && k != x)
        {
            if (k == 0 || k == x)
                arr[k] = 1;
            else
                arr[k] = str[0] - '0';
            k++;
        }
        str++;
    }
    return (arr);
}

int *surround(char *str, int size)
{
    int *i_str;
    int k;

    k = 0;
    i_str = (int *)malloc(sizeof(int) * size);
    while (k != size)
    {
        i_str[k] = 1;
        k++;
    }
    return (i_str);
}

int ft_initread(char *str, t_env *all)
{
    t_env *current;
    int fd;
    int index;
    char buf[42];

    index = 0;
    current = all;
    ft_bzero(buf, 42);
    if (!(fd = open(str, O_RDONLY)))
    {
        ft_putendl("Not valid file");
        exit(1);
    }
    current->map = (int **)malloc(sizeof(int *) * HEIGHT_MAP);
    while (0 < (read(fd, &buf, 36)))
    {
        buf[37] = '\0';
        printf("%s", buf);
        if (index == 0 || index == HEIGHT_MAP)
            current->map[index] = surround(buf, WIDTH_MAP);
        else
            current->map[index] = parse(buf, WIDTH_MAP);
        ft_bzero(buf, 42);
        index++;
    }
    printf("\n\n");
    close(fd);
    return (0);
}
