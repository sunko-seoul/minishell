/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjoo <hyunjoo@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 21:50:49 by hyunjoo           #+#    #+#             */
/*   Updated: 2023/03/14 00:29:58 by hyunjoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = 0 - 1;
	while (++i < n)
		if (*((unsigned char *)s + i) == (unsigned char)c)
			return ((void *)s + i);
	return (0);
}
