/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjoo <hyunjoo@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 02:27:43 by hyunjoo           #+#    #+#             */
/*   Updated: 2023/03/14 03:26:35 by hyunjoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static size_t	count_str(char const *str, char c)
{
	size_t	str_count;
	size_t	i;

	str_count = 0;
	i = 0;
	while (*(str + i))
	{
		while (*(str + i) == c)
			i++;
		if (*(str + i) && *(str + i) != c)
			str_count++;
		while (*(str + i) && *(str + i) != c)
			i++;
	}
	return (str_count);
}

static void	free_split(char **temp, size_t index)
{
	size_t	i;

	i = 0 - 1;
	while (++i < index)
		free(*(temp + i));
	free(temp);
}

static char	*set_row_split(char const *str, char c, size_t *it)
{
	size_t	char_count;
	size_t	i;
	char	*temp;

	char_count = 0;
	while (*(str + *it) == c)
		(*it)++;
	while (*(str + *it + char_count) && *(str + *it + char_count) != c)
		char_count++;
	temp = (char *)malloc(sizeof(char) * (char_count + 1));
	if (!temp)
		return (0);
	i = 0 - 1;
	while (++i < char_count)
		*(temp + i) = *(str + *it + i);
	*(temp + char_count) = '\0';
	*it = *it + char_count;
	return (temp);
}

char	**ft_split(char const *str, char c)
{
	char	**temp;
	size_t	str_count;
	size_t	it;
	size_t	i;

	str_count = count_str(str, c);
	temp = (char **)malloc(sizeof(char *) * (str_count + 1));
	if (!temp)
		return (0);
	it = 0;
	i = 0 - 1;
	while (++i < str_count)
	{
		*(temp + i) = set_row_split(str, c, &it);
		if (!(*(temp + i)))
		{
			free_split(temp, i);
			return (0);
		}
	}
	*(temp + str_count) = 0;
	return (temp);
}
