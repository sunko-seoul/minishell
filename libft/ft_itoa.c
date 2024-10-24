/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjunl <hyunjunl@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 12:52:30 by hyunjunl          #+#    #+#             */
/*   Updated: 2023/11/20 07:53:55 by hyunjunl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static size_t	get_str_len(int n)
{
	size_t	len;

	len = n <= 0;
	while (n)
	{
		++len;
		n /= 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*ret;
	size_t	len;
	size_t	neg;
	int		r;

	len = get_str_len(n);
	ret = ft_calloc(len + 1, sizeof(char));
	neg = n < 0;
	if (neg)
		ret[0] = '-';
	else
		n *= -1;
	while (len > neg)
	{
		r = n % 10;
		ret[--len] = '0' - r;
		n /= 10;
	}
	return (ret);
}
