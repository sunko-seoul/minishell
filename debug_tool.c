/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_tool.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 14:33:57 by sunko             #+#    #+#             */
/*   Updated: 2023/11/07 16:45:41 by sunko            ###   ########.fr       */
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

void	execute_tree(t_tree_token *node)
{
	if (!node || !node->u_value.value || !node->u_value.list)
		return ;
	if (node->is_list == 0)
		printf("%s\n", node->u_value.value);
	if (node->is_list == 1)
	{
		int i = 0;
		while (node->u_value.list[i])
		{
			printf("%s ", node->u_value.list[i]);
			i++;
		}
		printf("\n");
	}
}

void	search_tree(t_tree_token *node)
{
	execute_tree(node);
	if (node->left != NULL)
		search_tree(node->left);
	if (node->right != NULL)
		search_tree(node->right);
}


void	tree_debug(t_tree *tree)
{
	printf("\n======= syntax tree ============\n");
	search_tree(tree->root);
	printf("\n");
}



