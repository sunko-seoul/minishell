/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjunl <hyunjunl@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:16:31 by hyunjunl          #+#    #+#             */
/*   Updated: 2023/10/22 14:03:17 by hyunjunl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_putstr_fd(const char *s, int fd)
{
	if (s == 0)
		return (1);
	while (*s)
		if (ft_putchar_fd(*s++, fd))
			return (1);
	return (0);
}
