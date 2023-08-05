/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjoo <hyunjoo@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 01:06:35 by hyunjoo           #+#    #+#             */
/*   Updated: 2023/03/14 01:18:45 by hyunjoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_calloc(size_t count, size_t size)
{
	void	*temp;
	size_t	i;

	temp = (void *)malloc(count * size);
	if (!temp)
		return (0);
	i = 0 - 1;
	while (++i < count * size)
		*((char *)temp + i) = '\0';
	return (temp);
}
