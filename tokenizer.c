/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 17:42:50 by sunko             #+#    #+#             */
/*   Updated: 2023/11/27 16:02:15 by hyunjunl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include "minishell.h"

static t_token	*create_token(char *value, t_token_type type)
{
	t_token	*new_tok;

	new_tok = ft_calloc(1, sizeof(t_token));
	new_tok->value = value;
	new_tok->type = type;
	return (new_tok);
}

static void	push_back_token(t_token_lst *lst, t_token *token)
{
	if (lst->head == 0)
	{
		lst->head = token;
		lst->tail = token;
	}
	else
	{
		lst->tail->next = token;
		token->prev = lst->tail;
		lst->tail = token;
	}
}

static char	*get_word(char *string)
{
	const char *const	delimiter = "&|><() \t";
	char				*end_ptr;

	end_ptr = string;
	while (!ft_strchr(delimiter, *end_ptr))
	{
		if (*end_ptr == '\'' || *end_ptr == '\"')
			end_ptr = ft_strchr(end_ptr + 1, *end_ptr);
		end_ptr++;
	}
	return (ft_substr(string, 0, end_ptr - string));
}

static t_token	*get_token(char *string)
{
	int					t_idx;
	const char *const	operator[] = {"&&", "||", ">>", "<<", \
									"|", "(", ")", ">", "<", "&", 0};

	t_idx = 0;
	while (operator[t_idx])
	{
		if (!ft_strncmp(operator[t_idx], string, ft_strlen(operator[t_idx])))
			return (create_token(ft_strdup(operator[t_idx]), t_idx));
		t_idx++;
	}
	return (create_token(get_word(string), t_idx));
}

void	tokenize(t_token_lst *tok_lst, char *line)
{
	t_token	*new_tok;

	while (*line)
	{
		if (*line == ' ' || *line == '\t')
		{
			line++;
			continue ;
		}
		new_tok = get_token(line);
		line += ft_strlen(new_tok->value);
		push_back_token(tok_lst, new_tok);
	}
}
