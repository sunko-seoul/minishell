/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_tool.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 14:33:57 by sunko             #+#    #+#             */
/*   Updated: 2023/11/13 23:08:35 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dump_local_symtab(t_symtab_stack *sym_stack)
{
	t_symtab	*symtab;
	int			i;
	int			indent;

	symtab = sym_stack->local_symtab;
	i = 0;
	indent = symtab->level * 4;

	printf("%*sSymbol table [Level %d]:\r\n", indent, " ", symtab->level);
	printf("%*s===========================\r\n", indent, " ");
	printf("%*s  No               Symbol                    Val\r\n", indent, " ");
	printf("%*s------ -------------------------------- ------------\r\n", indent, " ");

	t_symtab_entry	*entry = symtab->first;
	while (entry)
	{
		printf("%*s[%04d] %-32s '%s'\r\n", indent, " ", i++, entry->name, entry->val);
		entry = entry->next;
	}
	printf("%*s------ -------------------------------- ------------\r\n", indent, " ");
}

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
	if (!node || (!node->u_value.value && !node->u_value.list))
		return ;
	if (node->is_list == 0)
	{
		printf("type = %d value = ", node->tok_type);
		printf("%s\n", node->u_value.value);
	}
	if (node->is_list == 1)
	{
		int i = 0;
		printf("type = %d value = ", node->tok_type);
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
