/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjoo <hyunjoo@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 03:47:18 by hyunjoo           #+#    #+#             */
/*   Updated: 2023/03/14 03:51:07 by hyunjoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

static void	print_number(int n, int fd)
{
	char	temp;

	if (!n)
		return ;
	print_number(n / 10, fd);
	temp = n % 10 + '0';
	write(fd, &temp, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
		write(fd, "-2147483648", 11);
	else if (n < 0)
	{
		write(fd, "-", 1);
		n *= -1;
	}
	else if (!n)
		write(fd, "0", 1);
	if (n && n != -2147483648)
		print_number(n, fd);
}
