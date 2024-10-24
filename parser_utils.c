/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 00:15:08 by sunko             #+#    #+#             */
/*   Updated: 2023/11/27 16:01:18 by hyunjunl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include <unistd.h>
#include "minishell.h"

void	free_all_tree_node(t_tree_node *root)
{
	if (root == 0)
		return ;
	if (root->type == TN_HEREDOC && root->sibling
		&& ft_strncmp(root->sibling->value, "/tmp/sh-thd-", 12) == 0)
		unlink(root->sibling->value);
	free_all_tree_node(root->child);
	free_all_tree_node(root->sibling);
	if (root->value)
		free(root->value);
	free(root);
}

int	expect_type(t_token **cur, t_token_type type)
{
	if (*cur && (*cur)->type == type)
	{
		*cur = (*cur)->next;
		return (1);
	}
	return (0);
}

t_tree_node	*create_tree_node(t_tree_node_type type, char *value)
{
	t_tree_node	*new_node;

	new_node = ft_calloc(1, sizeof(t_tree_node));
	new_node->type = type;
	if (value)
		new_node->value = ft_strdup(value);
	return (new_node);
}

t_tree_node	*push_back_sibling(t_tree_node *first_sibling,
									t_tree_node *last_sibling)
{
	t_tree_node	*cur_sibling;

	if (!last_sibling)
		return (0);
	cur_sibling = first_sibling;
	while (cur_sibling->sibling)
		cur_sibling = cur_sibling->sibling;
	cur_sibling->sibling = last_sibling;
	return (last_sibling);
}

t_tree_node	*create_parent_tree_node(t_tree_node_type type, t_tree_node *child)
{
	t_tree_node	*parent;

	parent = create_tree_node(type, 0);
	parent->child = child;
	return (parent);
}
