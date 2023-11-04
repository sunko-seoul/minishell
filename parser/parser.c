/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 16:32:04 by sunko             #+#    #+#             */
/*   Updated: 2023/11/04 14:28:41 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	next_sym(t_token_list *list)
{
	if (list->cur != list->tail)
	{
		list->before = list->cur;
		list->cur = list->cur->next;
	}
	else
	{
		list->before = list->cur;
		list->cur = NULL;
	}
}

int	sym_accept(t_token_list *list, t_token_type type)
{
	if (!list->cur)
		return (0);
	if (list->cur->type == type)
	{
		next_sym(list);
		return (1);
	}
	return (0);
}

int	sym_expect(t_token_list *list, t_token_type type)
{
	if (sym_accept(list, type))
		return (1);
	perror("expect: unexpected symbol");
	return (0);
}

void	add_child(t_tree *tree, t_tree_token *new_tok)
{
	new_tok->next = NULL;
	new_tok->child = NULL;
	if (!tree->root)
	{
		tree->root = new_tok;
		tree->first_child = new_tok;
		tree->last_child = new_tok;
		return ;
	}
	tree->last_child->child = new_tok;
	tree->last_child = new_tok;
}

void	add_next(t_tree_token *child_tok, t_tree_token *new_tok)
{
	t_tree_token	*cur_tok;

	if (!child_tok || !new_tok)
		return ;
	new_tok->next = NULL;
	new_tok->child = NULL;
	cur_tok = child_tok;
	while (cur_tok->next)
		cur_tok = cur_tok->next;
	cur_tok->next = new_tok;
}
