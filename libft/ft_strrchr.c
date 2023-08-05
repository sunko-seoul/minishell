/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjoo <hyunjoo@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 21:50:29 by hyunjoo           #+#    #+#             */
/*   Updated: 2023/03/14 01:03:05 by hyunjoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strrchr(const char *s, int c)
{
	size_t	len;

	len = 0;
	while (*(s + len))
		len++;
	if (!(char)c)
		return ((char *)s + len);
	while (len)
	{
		if (!(len--))
			break ;
		if (*(s + len) == (char)c)
			return ((char *)s + len);
	}
	return (0);
}
