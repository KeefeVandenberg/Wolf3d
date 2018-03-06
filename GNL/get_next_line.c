/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvandenb <kvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/05 16:56:34 by kvandenb          #+#    #+#             */
/*   Updated: 2018/03/06 10:52:42 by kvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char			*concat(char *str1, char *str2, int mall_1, int mall_2)
{
	int		len1;
	int		len2;
	char	*ans;

	len1 = 0;
	len2 = 0;
	while (str1[len1])
		len1++;
	while (str2[len2])
		len2++;
	ans = (char*)malloc(sizeof(char) * (len1 + len2 + 1));
	if (!ans)
		return (NULL);
	len1 = -1;
	len2 = -1;
	while (str1[++len1])
		ans[len1] = str1[len1];
	while (str2[++len2])
		ans[len1 + len2] = str2[len2];
	if (mall_1)
		free(str1);
	if (mall_2)
		free(str2);
	ans[len1 + len2] = '\0';
	return (ans);
}

int				scan(char *str, int newline)
{
	int		index;

	index = 0;
	while (str[index] != '\0')
	{
		if (str[index] == DELIM && newline)
			return (index);
		index++;
	}
	if (newline)
		return (-1);
	return (index);
}

int				copy(char *src, char **dst, char **stat, int fd)
{
	int		index;
	int		len;
	int		ret;

	ret = 0;
	len = 0;
	while ((src[len] != DELIM) && (src[len] != '\0'))
		len++;
	dst[0] = (char*)malloc(sizeof(char) * len + 1);
	index = 0;
	while ((src[index] != DELIM) && (src[index] != '\0'))
	{
		dst[0][index] = src[index];
		index++;
	}
	dst[0][index] = '\0';
	if (src[index] == DELIM)
	{
		ret = 1;
		stat[fd] = concat(&(src[++index]), "", 0, 0);
	}
	free(src);
	return (ret);
}

int				cleanup(char **stat, int fd, char *buff, char *ret)
{
	if (stat[fd])
		free(stat[fd]);
	free(buff);
	free(ret);
	return (-1);
}

int				get_next_line(const int fd, char **line)
{
	static char		*stat[15000];
	int				br;
	char			*buffer;
	char			*ret;

	br = 1;
	if (fd < 0 || (line == NULL) || BUFF_SIZE <= 0)
		return (-1);
	if (stat[fd] != NULL)
		ret = concat(stat[fd], "", 1, 0);
	else
		ret = concat("", "", 0, 0);
	stat[fd] = NULL;
	while ((scan(ret, 1) == -1) && br)
	{
		buffer = (char*)malloc(sizeof(char) * (BUFF_SIZE + 1));
		br = read(fd, buffer, BUFF_SIZE);
		if (br == -1)
			return (cleanup(stat, fd, buffer, ret));
		buffer[br] = '\0';
		ret = concat(ret, buffer, 1, 1);
	}
	if ((copy(ret, line, stat, fd) == 0) && (br == 0) && (scan(ret, 0) == 0))
		return (0);
	return (1);
}