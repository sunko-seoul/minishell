/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjunl <hyunjunl@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 22:48:24 by hyunjunl          #+#    #+#             */
/*   Updated: 2023/11/17 09:05:07 by hyunjunl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*ptr;
	size_t	len;

	len = count * size;
	if (count == 0 || (len % count == 0 && len / count == size))
	{
		ptr = malloc(len);
		if (ptr)
		{
			ft_bzero(ptr, len);
			return (ptr);
		}
	}
	ft_putendl_fd("ft_calloc error", 2);
	exit(1);
}
