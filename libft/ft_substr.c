/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjoo <hyunjoo@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 01:24:28 by hyunjoo           #+#    #+#             */
/*   Updated: 2023/03/14 01:45:47 by hyunjoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*temp;
	size_t	end;
	size_t	i;

	end = 0;
	while (*(s + end))
		end++;
	if (end < start)
		end = start;
	if (end - start >= len)
		end = start + len;
	temp = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!temp)
		return (0);
	i = 0 - 1;
	while (++i + start < end)
		*(temp + i) = *(s + start + i);
	*(temp + i) = '\0';
	return (temp);
}
