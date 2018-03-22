/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvandenb <kvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 17:21:48 by kvandenb          #+#    #+#             */
/*   Updated: 2018/03/21 18:03:04 by kvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		*parse(char *str, int x)
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

int		*surround(char *str, int size)
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

void	ft_finish_malloc(int index, t_env *e)
{
	t_env *all;

	all = e;
	while (index != HEIGHT_MAP - 1)
	{
		all->map[index] = malloc(sizeof(int *) * 5);
		index++;
	}
}

int		ft_check_validread(char *buf, int fd, t_env *all, int index)
{
	int i;

	if (fd < 0)
	{
		ft_finish_malloc(index, all);
		ft_putendl("Error : not a valid file");
		ft_exit(all);
	}
	if (index < HEIGHT_MAP - 1 || all->bytes_read < 36)
	{
		ft_finish_malloc(index, all);
		ft_putendl("Error : map input is too small or characters in map");
		ft_exit(all);
	}
	read(fd, &buf, 1);
	i = ft_strlen(buf);
	if (i == 0)
		return (1);
	if (i > 0)
	{
		ft_putendl("Error : map input is either invalid or too big");
		ft_exit(all);
	}
	return (0);
}

int		ft_initread(char *str, t_env *current)
{
	int		fd;
	int		index;
	char	buf[42];

	index = -1;
	ft_bzero(buf, 42);
	current->map = (int **)malloc(sizeof(int **) * HEIGHT_MAP);
	if (0 > (fd = open(str, O_RDONLY)))
		ft_check_validread(buf, fd, current, index + 1);
	while ((current->bytes_read =
		(read(fd, &buf, 36))) && index++ != HEIGHT_MAP - 1)
	{
		if ((ft_checkcharacters(buf)) == 0)
			ft_check_validread(buf, fd, current, index);
		current->map[index] = ((index == 0 || index == HEIGHT_MAP)
			? surround(buf, WIDTH_MAP) : parse(buf, WIDTH_MAP));
		if (ft_strlen(ft_strstr(buf, "\n")) > 1 || current->bytes_read < 36)
			ft_check_validread(buf, fd, current, index);
		ft_bzero(buf, 42);
	}
	current->bytes_read = 36;
	ft_check_validread(buf, fd, current, index);
	close(fd);
	return (0);
}
