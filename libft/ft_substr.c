/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjunl <hyunjunl@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 12:09:00 by hyunjunl          #+#    #+#             */
/*   Updated: 2023/11/17 16:51:29 by hyunjunl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ret;
	size_t	sz;

	if (s == 0)
		return (0);
	while (start-- && *s)
		++s;
	sz = 0;
	while (sz < len && s[sz])
		++sz;
	ret = ft_calloc(sz + 1, sizeof(char));
	ft_strlcpy(ret, s, sz + 1);
	return (ret);
}
