/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjunl <hyunjunl@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 22:51:38 by hyunjunl          #+#    #+#             */
/*   Updated: 2023/11/22 05:12:45 by hyunjunl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*s2;
	size_t	len;

	if (s1 == 0)
		return (0);
	len = ft_strlen(s1);
	s2 = ft_calloc(len + 1, sizeof(char));
	ft_strlcpy(s2, s1, len + 1);
	return (s2);
}
