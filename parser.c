/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 22:33:40 by sunko             #+#    #+#             */
/*   Updated: 2023/11/27 14:14:19 by hyunjunl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include "minishell.h"

static t_tree_node	*parse_io_redir(t_token **cur_tok)
{
	t_tree_node	*redir_child;

	redir_child = create_tree_node((t_tree_node_type)(*cur_tok)->type, 0);
	*cur_tok = (*cur_tok)->next;
	if (*cur_tok && (*cur_tok)->type == T_WORD)
	{
		push_back_sibling(redir_child,
			create_tree_node(TN_WORD, (*cur_tok)->value));
		*cur_tok = (*cur_tok)->next;
	}
	else
	{
		free_all_tree_node(redir_child);
		return (0);
	}
	return (create_parent_tree_node(TN_IO_REDIR, redir_child));
}

static t_tree_node	*parse_cmd_elem(t_sh_info *sh_info, t_token **cur_tok)
{
	t_tree_node	*cmd_elem_child;

	if (*cur_tok && (*cur_tok)->type == T_WORD)
	{
		cmd_elem_child = create_tree_node(TN_WORD, (*cur_tok)->value);
		*cur_tok = (*cur_tok)->next;
	}
	else if (*cur_tok
		&& ((*cur_tok)->type == T_APPEND
			|| (*cur_tok)->type == T_HEREDOC
			|| (*cur_tok)->type == T_IN_REDIR
			|| (*cur_tok)->type == T_OUT_REDIR))
	{
		cmd_elem_child = parse_io_redir(cur_tok);
		if (!cmd_elem_child || (cmd_elem_child->child->type == TN_HEREDOC
				&& process_heredoc(sh_info, cmd_elem_child->child->sibling)))
		{
			free_all_tree_node(cmd_elem_child);
			return (0);
		}
	}
	else
		return (0);
	return (create_parent_tree_node(TN_CMD_ELEM, cmd_elem_child));
}

static t_tree_node	*parse_cmd(t_sh_info *sh_info, t_token **cur_tok)
{
	t_tree_node	*cmd_child;

	cmd_child = parse_cmd_elem(sh_info, cur_tok);
	if (!cmd_child)
		return (0);
	while (*cur_tok
		&& ((*cur_tok)->type == T_WORD
			|| (*cur_tok)->type == T_APPEND
			|| (*cur_tok)->type == T_HEREDOC
			|| (*cur_tok)->type == T_IN_REDIR
			|| (*cur_tok)->type == T_OUT_REDIR))
	{
		if (!push_back_sibling(cmd_child, parse_cmd_elem(sh_info, cur_tok)))
		{
			free_all_tree_node(cmd_child);
			return (0);
		}
	}
	return (create_parent_tree_node(TN_CMD, cmd_child));
}

static t_tree_node	*parse_expr(t_sh_info *sh_info, t_token **cur_tok)
{
	t_tree_node	*expr_child;

	if (expect_type(cur_tok, T_OPEN_BRAKET))
	{
		expr_child = parse_list(sh_info, cur_tok);
		if (expr_child && expect_type(cur_tok, T_CLOSE_BRAKET))
			return (create_parent_tree_node(TN_EXPR, expr_child));
		free_all_tree_node(expr_child);
		return (0);
	}
	expr_child = parse_cmd(sh_info, cur_tok);
	if (!expr_child)
		return (0);
	while (expect_type(cur_tok, T_PIPE))
	{
		if (!push_back_sibling(expr_child, parse_cmd(sh_info, cur_tok)))
		{
			free_all_tree_node(expr_child);
			return (0);
		}
	}
	return (create_parent_tree_node(TN_EXPR, expr_child));
}

t_tree_node	*parse_list(t_sh_info *sh_info, t_token **cur_tok)
{
	t_tree_node	*list_child;

	list_child = parse_expr(sh_info, cur_tok);
	if (!list_child)
		return (0);
	while (*cur_tok
		&& ((*cur_tok)->type == T_LOGICAL_AND
			|| (*cur_tok)->type == T_LOGICAL_OR))
	{
		push_back_sibling(list_child,
			create_tree_node((t_tree_node_type)(*cur_tok)->type, 0));
		*cur_tok = (*cur_tok)->next;
		if (!push_back_sibling(list_child, parse_expr(sh_info, cur_tok)))
		{
			free_all_tree_node(list_child);
			return (0);
		}
	}
	return (create_parent_tree_node(TN_LIST, list_child));
}
