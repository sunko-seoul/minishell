/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjunl <hyunjunl@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 06:53:45 by hyunjunl          #+#    #+#             */
/*   Updated: 2024/02/04 05:31:35 by hyunjunl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	handle_error(int *err)
{
	if (err)
		*err = 1;
	return (0);
}

static char	*skip_space(char *str)
{
	while (ft_isspace(*str))
		++str;
	return (str);
}

long long	ft_atoll(char *str, int *err)
{
	long long	num;
	long long	tmp;
	int			neg;

	str = skip_space(str);
	num = 0;
	neg = 0;
	if (*str == '+' || *str == '-')
		neg = (*str++ == '-');
	if (!ft_isdigit(*str))
		return (handle_error(err));
	while (ft_isdigit(*str))
	{
		tmp = 10 * num - (*str - '0');
		if (tmp / 10 != num || tmp % 10 != -(*str - '0'))
			break ;
		num = tmp;
		++str;
	}
	str = skip_space(str);
	if (*str || (!neg && num == -num))
		return (handle_error(err));
	if (!neg)
		num *= -1;
	return (num);
}
