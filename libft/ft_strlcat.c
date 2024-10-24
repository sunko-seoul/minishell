/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjunl <hyunjunl@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 21:51:41 by hyunjunl          #+#    #+#             */
/*   Updated: 2023/10/06 11:12:01 by hyunjunl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	len;

	if (dst == 0 || src == 0)
		return (0);
	len = 0;
	while (len < dstsize && *dst)
	{
		++dst;
		++len;
	}
	while (len + 1 < dstsize && *src)
	{
		*dst++ = *src++;
		++len;
	}
	if (len < dstsize)
		*dst = '\0';
	while (*src++)
		++len;
	return (len);
}
