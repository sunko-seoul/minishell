/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjoo <hyunjoo@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 03:05:16 by hyunjoo           #+#    #+#             */
/*   Updated: 2023/03/14 03:30:38 by hyunjoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static char	*set_itoa(long num, int len)
{
	char	*temp;
	long	check;

	temp = (char *)malloc(sizeof(char) * (len + 1));
	if (!temp)
		return (0);
	temp[len] = '\0';
	check = num;
	while (--len >= 0)
	{
		if (!check)
			temp[len] = '0';
		else if (!num)
			temp[len] = '-';
		else
		{
			temp[len] = num % 10 + '0';
			num /= 10;
		}
	}
	return (temp);
}

char	*ft_itoa(int n)
{
	int		len;
	long	num;
	long	dup;

	len = 0;
	num = n;
	dup = n;
	if (!num)
		len++;
	if (num < 0)
	{
		num *= (-1);
		dup *= (-1);
		len++;
	}
	while (num)
	{
		len++;
		num /= 10;
	}
	return (set_itoa(dup, len));
}
