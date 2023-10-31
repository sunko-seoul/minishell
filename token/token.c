/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 10:37:26 by sunko             #+#    #+#             */
/*   Updated: 2023/10/31 14:01:01 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "token.h"

t_token	*create_token(void)
{
	t_token		*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (!new_token)
	{
		perror("malloc : ");
		exit(EXIT_FAILURE);
	}
	new_token->next = NULL;
	return new_token;
}

void	token_push_back(t_token_list *list, t_token *token)
{
	list->num_of_data += 1;
	if (list->head == NULL)
	{
		list->head = token;
		list->tail = token;
		list->cur = list->head;
	}
	else
	{
		while (list->cur->next != NULL)
			list->cur = list->cur->next;
		list->cur->next = token;
		list->tail = token;
	}
}

t_token_list	*create_token_list(void)
{
	t_token_list	*new_list;

	new_list = (t_token_list *)malloc(sizeof(t_token_list));
	if (!new_list)
		return (NULL);
	new_list->cur = NULL;
	new_list->head = NULL;
	new_list->tail = NULL;
	new_list->num_of_data = 0;
	return (new_list);
}

size_t	find_close_quote(char *str)
{
	char	quote;
	size_t	idx;
	size_t	len;

	quote = str[0];
	if (quote != '\'' && quote != '\"')
		return	(0);
	idx = 0;
	len = ft_strlen(str);
	while (++idx < len)
	{
		if (str[idx] == quote)
			return (idx);
	}
	return 0;
}

int	ft_is_not_word(char c)
{
	return (c == '&' || c == '|' || c == '*' || c == '>' || c == '<' || \
	c == '(' || c == ')');
}
