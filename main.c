/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvandenb <kvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 19:37:37 by kvandenb          #+#    #+#             */
/*   Updated: 2018/02/15 18:38:49 by kvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int parse(t_read *current, char *str, int y, int x)
{
    t_read *new;
    t_read *last;

    new = current;
    while (new->next != NULL)
        new = new->next;
    if (!(new->next = malloc(sizeof(t_read))))
        return (-1);
    new->x = x;
    new->y = y;
    new->height = atoi(str);
    last = new;
    new = new->next;
    new->next = NULL;
    new->last = last;
    return (1);
}

int init_parse(t_read *current, char *str, int y)
{
    int i;
    int x;

    i = 0;
    x = -1;
    while(str[i])
    {
        if (ft_isdigit(str[i]))
            parse(current, str, y, x++);
        i++;
    }
    return (1);
}

int ft_initread(char *str, t_read *all)
{
    t_read *current;
    int fd;
    char *line;
    int y;

    y = 0;
    line = NULL;
    current = all;
    fd = open(str, O_RDONLY);
    while (get_next_line(fd, &line) != 0)
    {
        init_parse(current, line, y);
        line = 0;
        y++;
    }
    close(fd);
    return (0);
}

int main(int argc, char **argv)
{
    t_read *head;

    head = malloc(sizeof(t_read));
    head->next = NULL;
    if (argc == 2)
    {
        ft_initread(argv[1], head);
        //ft_mapper(head, map);
    }
}