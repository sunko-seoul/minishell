/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_tool.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 14:33:57 by sunko             #+#    #+#             */
/*   Updated: 2023/11/04 14:36:34 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	token_debug(t_token_list *token_list)
{
	token_list->cur = token_list->head;
	printf("\n----   type   ----   string   ----\n");
	while (token_list->cur != NULL)
	{
		printf("        %d    ", token_list->cur->type);
		printf("        %s    \n", token_list->cur->value);
		token_list->cur = token_list->cur->next;
	}
	token_list->cur = token_list->head;
}

void	tree_debug(t_tree *tree)
{
	printf("\n======= syntax tree ============\n");
	tree->cur = tree->first_child;
	t_tree_token	*cur_child;
	cur_child = tree->first_child;
	int i = 0;
	while (cur_child)
	{
		tree->cur = cur_child;
		printf("%d child : ", ++i);
		while (tree->cur)
		{
			printf("%s ", tree->cur->value);
			tree->cur = tree->cur->next;
		}
		printf("\n");
		cur_child = cur_child->child;
	}
	printf("\n");
}


