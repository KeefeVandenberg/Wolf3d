/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvandenb <kvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 19:37:37 by kvandenb          #+#    #+#             */
/*   Updated: 2018/02/15 19:57:30 by kvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int ft_mapper(t_read *head, t_map *map)
{
    t_read *e;
    t_read *tmp;

    e = head;
    map = malloc(sizeof(t_map));
    while(head->next)
    {
        tmp = ft_find_struct(head->x + 1, head->y, head);
        tmp == NULL ? map->right = NULL : ft_read_to_map(tmp, map->right);
        tmp = ft_find_struct(head->x, head->y + 1, head);
        tmp == NULL ? map->up = NULL : ft_read_to_map(tmp, map->up);
        tmp = ft_find_struct(head->x - 1, head->y, head);
        tmp == NULL ? map->left = NULL : ft_read_to_map(tmp, map->left);
        tmp = ft_find_struct(head->x, head->y - 1, head);
        tmp == NULL ? map->down = NULL : ft_read_to_map(tmp, map->down);
    } 
}

t_read *ft_find_struct(int x, int y, t_read *head)
{
    if (x - 1 < 0)
        return (NULL);
    if (y - 1 < 0)
        return (NULL);
    while (1)
    {
        if (head->x == x && head->y == y)
            return (head);
        if (head->next == NULL)
            return (NULL);
        head = head->next;
    }
}

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
    t_map *map;

    head = malloc(sizeof(t_read));
    head->next = NULL;
    if (argc == 2)
    {
        ft_initread(argv[1], head);
        ft_mapper(head, map);
    }
}