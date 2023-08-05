/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjoo <hyunjoo@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 21:12:48 by hyunjoo           #+#    #+#             */
/*   Updated: 2023/03/14 00:58:52 by hyunjoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	dst_len;
	size_t	src_len;

	dst_len = 0;
	while (*(dst + dst_len))
		dst_len++;
	src_len = 0;
	while (*(src + src_len))
		src_len++;
	if (dst_len > dstsize)
		return (src_len + dstsize);
	i = 0;
	while (i + dst_len + 1 < dstsize && *(src + i))
	{
		*(dst + dst_len + i) = *(src + i);
		i++;
	}
	if (dstsize)
		*(dst + dst_len + i) = '\0';
	return (dst_len + src_len);
}
