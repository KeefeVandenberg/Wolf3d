/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvandenb <kvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 17:21:48 by kvandenb          #+#    #+#             */
/*   Updated: 2018/03/06 16:01:33 by kvandenb         ###   ########.fr       */
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
    while (str[i])
    {
        if (ft_isdigit(str[i]) && k != x)
        {
            arr[k] = str[i] - 48;
            k++;
        }
        i++;
    }
    return (arr);
}

int ft_initread(char *str, t_env *all)
{
    t_env *current;
    int fd;
    char *line;
    int index;

    index = 0;
    line = NULL;
    current = all;
    if (!(fd = open(str, O_RDONLY)))
    {
        ft_putendl("Not valid file");
        exit(1);
    }
    current->map = (int **)malloc(sizeof(int) * HEIGHT_MAP);
    while (get_next_line(fd, &line) == 1)
    {
        current->map[index] = parse(line, WIDTH_MAP);
        //printf("%s\n", line);
        free(line);
        index++;
    }
    close(fd);
    return (0);
}
