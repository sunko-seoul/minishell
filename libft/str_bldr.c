/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_bldr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjunl <hyunjunl@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 05:33:10 by hyunjunl          #+#    #+#             */
/*   Updated: 2023/11/26 08:56:48 by hyunjunl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include "libft.h"

void	init_str_bldr(t_str_bldr *str_bldr)
{
	str_bldr->str = ft_strdup("");
	str_bldr->sz = 0;
	str_bldr->cap = 0;
}

void	append_str(t_str_bldr *str_bldr, char *str, size_t n)
{
	char	*new_arr;
	size_t	new_cap;

	if (str == 0)
		return ;
	if (str_bldr->sz + n > str_bldr->cap)
	{
		new_cap = 2 * str_bldr->cap;
		if (new_cap < str_bldr->sz + n)
			new_cap = str_bldr->sz + n;
		new_arr = ft_calloc(new_cap + 1, sizeof(char));
		ft_memcpy(new_arr, str_bldr->str, str_bldr->sz);
		free(str_bldr->str);
		str_bldr->str = new_arr;
		str_bldr->cap = new_cap;
	}
	ft_memcpy(str_bldr->str + str_bldr->sz, str, n);
	str_bldr->sz += n;
}

void	append_char(t_str_bldr *str_bldr, char c)
{
	append_str(str_bldr, &c, 1);
}
