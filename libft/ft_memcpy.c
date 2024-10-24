/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjunl <hyunjunl@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 21:15:32 by hyunjunl          #+#    #+#             */
/*   Updated: 2023/10/05 23:12:56 by hyunjunl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*c_dst;
	const char	*c_src;

	if (dst == 0 || src == 0)
		return (dst);
	c_dst = dst;
	c_src = src;
	while (n--)
		*c_dst++ = *c_src++;
	return (dst);
}
