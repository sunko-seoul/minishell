/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 23:04:15 by sunko             #+#    #+#             */
/*   Updated: 2023/10/25 23:21:30 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scanner.h"

void	add_to_buf(const char c, char **tok_buf, int *idx, int *size)
{
	char	*tmp;
	(*tok_buf)[(*idx)++] = c;
	if (*idx >= *size)
	{
		tmp = ft_realloc(*tok_buf, *size * 2);
		if (!tmp)
			return ;
		*tok_buf = tmp;
		*size *= 2;
	}
}

t_token	*tokenize(t_source *src)
{
	t_token	*tok;
	t_token eof_tok;
	char	*tok_buf;
	int		tok_bufsize;
	int		tok_bufindex;
	char	nc;
	char	nc2;
	int		i;

	eof_tok.src = 0;
	eof_tok.text = 0;
	eof_tok.text_len = 0;
	if (!src || !src->buffer || !src->bufsize)
		return	&eof_tok;
	tok_bufsize = 1024;
	tok_buf = malloc(tok_bufsize);
	if (!tok_buf)
		return &eof_tok;
	tok_bufsize = 0;
	tok_buf[0] = 0;

	nc = next_char(src);
	if (nc == ERRCHAR || nc == EOF)
		return &eof_tok;

}
