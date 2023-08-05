/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjoo <hyunjoo@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 21:51:06 by hyunjoo           #+#    #+#             */
/*   Updated: 2023/03/14 00:41:53 by hyunjoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < len && *(haystack + i))
	{
		j = 0 - 1;
		while (*(needle + ++j))
			if (*(haystack + i + j) != *(needle + j) || i + j >= len)
				break ;
		if (!(*(needle + j)))
			return ((char *)haystack + i);
		i++;
	}
	if (!(*needle))
		return ((char *)haystack);
	return (0);
}
