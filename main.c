/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvandenb <kvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 19:37:37 by kvandenb          #+#    #+#             */
/*   Updated: 2018/02/20 19:54:58 by kvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int struct_len(t_read *head, t_env *all)
{
    t_read *e;
    t_env *j;

    j = all;
    e = head;
    while (e->next->x > e->x)
    {
        e = e->next;
    }
    j->x_max = e->x;
    j->y_max = e->y;
    return (0);
}

int *fill_line(t_read *head, t_env *map)
{
    int *str;
    t_read *current;
    int i;

    current = head;
    str = (int *)malloc(sizeof(int) * map->x_max);
    while (i != map->x_max)
    {
        str[i] = current->height;
        //printf("%d\n", current->height);
        current = current->next;
        i++;
    }
    return (str);
}

/*
//I think I am going to need to scrap the parse function, at least a bit and then
//remake it so it doesnt even make a read and just creates an int array right off
//the bat but I do not know at the moment.
*/
int ft_mapper(t_read *head, t_env *map)
{
    t_env *e;
    int i;
    int index;
    

    index = 0;
    e = map;
    struct_len(head, e);
    e->map = (int **)malloc(sizeof(int *) * e->y_max);
    while(index != e->x_max + 1)
    {
        e->map[index] = fill_line(head, map);
        index++;
    }
    return (0);
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
    printf("%c\n", str[0]);
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
        str++;
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
    t_env *all;

    all = malloc(sizeof(t_env));
    head = malloc(sizeof(t_read));
    head->next = NULL;
    if (argc == 2)
    {
        ft_initread(argv[1], head);
        ft_mapper(head, all);
    }
}