/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 10:29:58 by sunko             #+#    #+#             */
/*   Updated: 2023/11/01 15:35:27 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "token.h"

t_token_list	*tokenizer(t_token_list *token_list, t_source *src)
{
	char			cur;

	while (peek_char(src) != EOF)
	{
		skip_white_space(src);
		cur = next_char(src);
		if (cur == '&')
			ampersand_token(token_list, src);
		else if (cur == '|')
			pipe_logical_or_token(token_list, src);
		else if (cur == '\'' || cur == '\"')
			quotes_token(token_list, src, cur);
		else if (cur == '*')
			asterisk_token(token_list);
		else if (cur == '>')
			right_redirection_token(token_list, src, cur);
		else if (cur == '<')
			left_redirection_token(token_list, src, cur);
		else if (cur == '(' || cur == ')')
			parentheses_token(token_list, cur);
		else
			word_token(token_list, src, cur);
	}
	token_list->cur = token_list->head;
	token_list->before = token_list->head;
	return (token_list);
}

void	ampersand_token(t_token_list *list, t_source *src)
{
	t_token		*new_token;
	char		next;

	next = peek_char(src);
	if (next != '&')
	{
		printf("not interpret ampersand\n");
		return ;
	}
	new_token = create_token();
	new_token->string = "&&";
	new_token->type = LOGICAL_END;
	next_char(src);
	token_push_back(list, new_token);
}

void	pipe_logical_or_token(t_token_list *list, t_source *src)
{
	t_token		*new_token;
	char		next;

	new_token = create_token();
	next = peek_char(src);
	if (next == '|')
	{
		new_token->string = "||";
		new_token->type = LOGICAL_OR;
		next_char(src);
	}
	else
	{
		new_token->string = "|";
		new_token->type = PIPE;
	}
	token_push_back(list, new_token);
}

void	quotes_token(t_token_list *list, t_source *src, char cur)
{
	t_token	*new_token;
	int		i;
	int		idx;

	i = 0;
	new_token = create_token();
	idx = find_close_quote(src->buffer + src->curpos);
	if (!idx)
	{
		printf("not interpret unclosed quotes\n");
		return ;
	}
	new_token->string = (char *)ft_malloc(sizeof(char) * (idx + 1));
	new_token->string[0] = cur;
	if (cur == '\'')
		new_token->type = SINGLE_QUOTE;
	else if (cur == '\"')
		new_token->type = DOUBLE_QUOTE;
	while (idx--)
		new_token->string[++i] = next_char(src);
	token_push_back(list, new_token);
}

void	asterisk_token(t_token_list *list)
{
	t_token	*new_token;

	new_token = create_token();
	new_token->string = "*";
	new_token->type = WILDCARD;
	token_push_back(list, new_token);
}
