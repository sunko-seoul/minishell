/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjoo <hyunjoo@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 20:54:39 by hyunjoo           #+#    #+#             */
/*   Updated: 2023/03/14 01:04:50 by hyunjoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	if (!dst && !src)
		return (dst);
	if (dst < src)
	{
		i = 0 - 1;
		while (++i < len)
			*((char *)dst + i) = *((char *)src + i);
	}
	else
	{
		while (len)
		{
			if (!(len--))
				break ;
			*((char *)dst + len) = *((char *)src + len);
		}
	}
	return (dst);
}
