/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjoo <hyunjoo@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 21:51:13 by hyunjoo           #+#    #+#             */
/*   Updated: 2023/03/14 05:26:12 by hyunjoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_atoi(const char *str)
{
	size_t	i;
	long	num;
	int		sign;

	sign = 1;
	num = 0;
	i = 0;
	while (*(str + i) == ' ' || (9 <= *(str + i) && *(str + i) <= 13))
		i++;
	if (*(str + i) == '-' || *(str + i) == '+')
		sign = 44 - *(str + i++);
	while ('0' <= *(str + i) && *(str + i) <= '9')
		num = num * 10 + *(str + i++) - '0';
	return (num * sign);
}
