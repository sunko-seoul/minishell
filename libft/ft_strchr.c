/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjoo <hyunjoo@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 21:20:25 by hyunjoo           #+#    #+#             */
/*   Updated: 2023/03/14 00:36:15 by hyunjoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	if (!(char)c)
	{
		i = 0;
		while (*(s + i))
			i++;
		return ((char *)s + i);
	}
	i = 0 - 1;
	while (*(s + ++i))
		if (*(s + i) == (char)c)
			return ((char *)s + i);
	return (0);
}
