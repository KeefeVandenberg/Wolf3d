/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvandenb <kvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 16:36:26 by kvandenb          #+#    #+#             */
/*   Updated: 2018/01/29 15:09:57 by kvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *s1, const void *s2, size_t n)
{
	void	*temp_s1;

	temp_s1 = s1;
	while (n--)
		*(unsigned char *)s1++ = *(unsigned char *)s2++;
	return (temp_s1);
}
