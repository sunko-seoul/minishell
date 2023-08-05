/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjoo <hyunjoo@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 01:46:58 by hyunjoo           #+#    #+#             */
/*   Updated: 2023/03/14 01:54:20 by hyunjoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*temp;
	size_t	s1_len;
	size_t	s2_len;
	size_t	i;

	s1_len = 0;
	while (*(s1 + s1_len))
		s1_len++;
	s2_len = 0;
	while (*(s2 + s2_len))
		s2_len++;
	temp = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!temp)
		return (0);
	i = 0 - 1;
	while (++i < s1_len)
		*(temp + i) = *(s1 + i);
	i = 0 - 1;
	while (++i < s2_len)
		*(temp + s1_len + i) = *(s2 + i);
	*(temp + s1_len + s2_len) = '\0';
	return (temp);
}
