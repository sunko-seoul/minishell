/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjunl <hyunjunl@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 12:26:47 by hyunjunl          #+#    #+#             */
/*   Updated: 2023/11/23 15:09:03 by hyunjunl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include "libft.h"

static size_t	count_tokens(char const *s, const char *sep)
{
	size_t	cnt;
	int		flag;

	cnt = 0;
	flag = 1;
	while (*s)
	{
		if (ft_strchr(sep, *s))
			flag = 1;
		else
		{
			if (flag)
				++cnt;
			flag = 0;
		}
		++s;
	}
	return (cnt);
}

static const char	*next_token(char const **sp, const char *sep)
{
	char const	*s;
	char const	*ret;

	s = *sp;
	while (ft_strchr(sep, *s))
		++s;
	ret = s;
	while (*s && ft_strchr(sep, *s) == 0)
		++s;
	*sp = s;
	return (ret);
}

static void	free_all(char **tokens, size_t token_cnt)
{
	while (token_cnt--)
		free(tokens[token_cnt]);
	free(tokens);
}

char	**ft_split(char const *s, const char *sep)
{
	char		**tokens;
	const char	*token;
	size_t		token_cnt;
	size_t		i;

	if (s == 0)
		return (0);
	token_cnt = count_tokens(s, sep);
	tokens = ft_calloc(token_cnt + 2, sizeof(char *));
	if (tokens == 0)
		return (0);
	i = 0;
	while (i < token_cnt)
	{
		token = next_token(&s, sep);
		tokens[i] = ft_substr(token, 0, s - token);
		if (tokens[i++] == 0)
		{
			free_all(tokens, i);
			tokens = 0;
			break ;
		}
	}
	return (tokens);
}
