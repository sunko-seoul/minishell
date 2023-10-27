/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   source.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 22:41:57 by sunko             #+#    #+#             */
/*   Updated: 2023/10/27 11:42:36 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "source.h"

void	init_src(char *cmd, t_source *src)
{
	src->buffer = cmd;
	src->bufsize = ft_strlen(cmd);
	src->curpos = INIT_SRC_POS;
}

void	unget_char(t_source *src)
{
	if (src->curpos < 0)
		return ;
	src->curpos--;
}

char	next_char(t_source *src)
{
	if (!src || !src->buffer)
		return (ERRCHAR);
	if (++src->curpos >= src->bufsize)
	{
		src->curpos = src->bufsize;
		return (EOF);
	}
	return (src->buffer[src->curpos]);
}

char	peek_char(t_source *src)
{
	int		pos;

	if (!src || !src->buffer)
		return(ERRCHAR);
	pos = src->curpos;
	if (++pos >= src->bufsize)
		return EOF;
	return src->buffer[pos];
}

void	skip_white_space(t_source *src)
{
	char	c;

	if (!src || !src->buffer)
		return ;
	c = peek_char(src);
	while (c != EOF)
	{
		if (peek_char(src) != ' ')
			break;
		else
			c = next_char(src);
	}
}
