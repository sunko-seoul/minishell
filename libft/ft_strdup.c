/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjoo <hyunjoo@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 01:19:49 by hyunjoo           #+#    #+#             */
/*   Updated: 2023/03/14 01:24:12 by hyunjoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strdup(const char *s1)
{
	size_t	i;
	size_t	len;
	char	*temp;

	len = 0;
	while (*(s1 + len))
		len++;
	temp = (char *)malloc(sizeof(char) * (len + 1));
	if (!temp)
		return (0);
	i = 0 - 1;
	while (++i < len)
		*(temp + i) = *(s1 + i);
	*(temp + i) = '\0';
	return (temp);
}
