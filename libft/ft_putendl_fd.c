/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjunl <hyunjunl@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:18:30 by hyunjunl          #+#    #+#             */
/*   Updated: 2023/10/22 14:03:25 by hyunjunl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_putendl_fd(const char *s, int fd)
{
	if (s == 0)
		return (1);
	return (ft_putstr_fd(s, fd) || ft_putchar_fd('\n', fd));
}
