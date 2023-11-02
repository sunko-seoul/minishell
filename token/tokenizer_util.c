/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 10:35:47 by sunko             #+#    #+#             */
/*   Updated: 2023/11/02 11:21:55 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "token.h"

void	left_redirection_token(t_token_list *list, t_source *src, char cur)
{
	t_token	*new_token;
	char	next;

	new_token = create_token();
	next = peek_char(src);
	if (cur == '<' && next == '<')
	{
		new_token->value = "<<";
		new_token->type = LEFT_APPEND;
		next_char(src);
	}
	else if (cur == '<' && next != '<')
	{
		new_token->value = "<";
		new_token->type = LEFT_REDIR;
	}
	token_push_back(list, new_token);
}

void	right_redirection_token(t_token_list *list, t_source *src, char cur)
{
	t_token	*new_token;
	char	next;

	new_token = create_token();
	next = peek_char(src);
	if (cur == '>' && next == '>')
	{
		new_token->value = ">>";
		new_token->type = RIGHT_APPEND;
		next_char(src);
	}
	else if (cur == '>' && next != '>')
	{
		new_token->value = ">";
		new_token->type = RIGHT_REDIR;
	}
	token_push_back(list, new_token);
}

void	word_token(t_token_list *list, t_source *src, char cur)
{
	t_token	*new_token;
	size_t	word_idx;
	int		word_size;

	new_token = create_token();
	word_idx = 0;
	word_size = 0;
	new_token->type = WORD;
	word_size = find_next_space(src->buffer + src->curpos);
	new_token->value = (char *)malloc(sizeof(char) * word_size + 1);
	new_token->value[0] = cur;
	while (word_size--)
		new_token->value[++word_idx] = next_char(src);
	new_token->value[word_idx] = '\0';
	token_push_back(list, new_token);
	if (ft_is_not_word(src->buffer[src->curpos]))
		unget_char(src);
}

void	parentheses_token(t_token_list *list, char cur)
{
	t_token	*new_token;

	new_token = create_token();
	if (cur == '(')
	{
		new_token->value = "(";
		new_token->type = LEFT_PAREN;
	}
	else if (cur == ')')
	{
		new_token->value = ")";
		new_token->type = RIGHT_PAREN;
	}
	token_push_back(list, new_token);
}

size_t	find_next_space(char *str)
{
	size_t	idx;

	idx = 0;
	while (str[idx] != ' ' && str[idx] != 0 && !ft_is_not_word(str[idx]))
		idx++;
	return idx;
}
