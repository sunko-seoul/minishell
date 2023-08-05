/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 12:02:09 by sunko             #+#    #+#             */
/*   Updated: 2023/08/05 12:03:04 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

t_node	*create_node(void)
{
	t_node	*new_node;
	t_token	*new_token;

	new_node = (t_node *)malloc(sizeof(t_node));
	if (!new_node)
		print_error();
	new_token = (t_token *)malloc(sizeof(t_token));
	if (!new_token)
		print_error();
	new_node->token = new_token;
	new_node->token->string = NULL;
	new_node->token->type = 0;
	new_node->next = NULL;
	return (new_node);
}

t_token_list	*create_token_list(void)
{
	t_token_list	*new_list;

	new_list = (t_token_list *)malloc(sizeof(t_token_list));
	if (!new_list)
		print_error();
	new_list->cur = NULL;
	new_list->head = NULL;
	new_list->tail = NULL;
	new_list->num_of_data = 0;
	return (new_list);
}

t_token	*create_token_sample(void)
{
	t_token	*token_sample;
	int		i;

	i = 0;
	token_sample = (t_token *)malloc(sizeof(t_token) * TOKEN_NUM);
	if (!token_sample)
		print_error();
	init_token(token_sample);
	return (token_sample);
}

void	push_back(t_token_list *token_list, t_node *node)
{
	token_list->num_of_data += 1;
	if (token_list->head == NULL ||  token_list->tail == NULL)
	{
		token_list->head = node;
		token_list->tail = node;
		token_list->cur = node;
		return ;
	}
	token_list->tail->next = node;
	token_list->tail = node;
}
