/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvandenb <kvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 17:21:48 by kvandenb          #+#    #+#             */
/*   Updated: 2018/03/14 21:08:28 by kvandenb         ###   ########.fr       */
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
            arr[k] = str[0] - '0';
            k++;
        }
        str++;
    }
    return (arr);
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
        current->map[index] = parse(buf, WIDTH_MAP);
        ft_bzero(buf, 42);
        index++;
    }
    printf("\n\n");
    current->map[index] = NULL;
    close(fd);
    return (0);
}
