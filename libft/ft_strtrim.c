/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjoo <hyunjoo@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 01:55:26 by hyunjoo           #+#    #+#             */
/*   Updated: 2023/03/14 02:25:23 by hyunjoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	is_setchar(char c, char const *set)
{
	size_t	i;

	i = 0 - 1;
	while (*(set + ++i))
		if (c == *(set + i))
			return (1);
	return (0);
}

static char	*make_trimed_str(char const *s1, size_t start, size_t end)
{
	char	*temp;
	size_t	i;

	if (start > end)
		start = end;
	temp = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!temp)
		return (0);
	i = 0 - 1;
	while (++i + start < end)
		*(temp + i) = *(s1 + start + i);
	*(temp + i) = '\0';
	return (temp);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	end;
	size_t	start;

	start = 0;
	while (*(s1 + start) && is_setchar(*(s1 + start), set))
		start++;
	end = 0;
	while (*(s1 + end))
		end++;
	while (end && *(s1 + end - 1) && is_setchar(*(s1 + end - 1), set))
		end--;
	return (make_trimed_str(s1, start, end));
}
