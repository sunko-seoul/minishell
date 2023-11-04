/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 14:29:35 by sunko             #+#    #+#             */
/*   Updated: 2023/11/04 14:30:26 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parse_paren(t_token_list *list, t_tree *tree)
{
	t_tree_token	*new_tok;

	new_tok = (t_tree_token *)ft_malloc(sizeof(t_tree_token));
	if (sym_accept(list, LEFT_PAREN))
	{
		new_tok->type = list->before->type;
		new_tok->value = list->before->value;
		add_child(tree, new_tok);
	}
	while (list->cur)
	{
		while (sym_accept(list, WORD) \
		|| sym_accept(list, SINGLE_QUOTE) \
		|| sym_accept(list, DOUBLE_QUOTE))
		{
			new_tok = (t_tree_token *)ft_malloc(sizeof(t_tree_token));
			new_tok->type = list->before->type;
			new_tok->value = list->before->value;
			add_next(tree->last_child, new_tok);
		}
		if (check_cur_type(list, PIPE))
			parse_pipe(list, tree);
		if (sym_accept(list, RIGHT_PAREN))
		{
			new_tok = (t_tree_token *)ft_malloc(sizeof(t_tree_token));
			new_tok->type = list->before->type;
			new_tok->value = list->before->value;
			add_next(tree->last_child, new_tok);
			return ;
		}
	}
	printf("not interpreted unclosed PAREN");
	exit(EXIT_FAILURE);
}



void	parse_quote(t_token_list *list, t_tree *tree)
{
	t_tree_token	*new_tok;

	new_tok = (t_tree_token *)ft_malloc(sizeof(t_tree_token));
	if (sym_accept(list, SINGLE_QUOTE) \
	|| sym_accept(list, DOUBLE_QUOTE))
	{
		new_tok->type = list->before->type;
		new_tok->value = list->before->value;
		add_child(tree, new_tok);
	}
	else
		return ;
	while (sym_accept(list, WORD) \
	|| sym_accept(list, SINGLE_QUOTE) \
	|| sym_accept(list, DOUBLE_QUOTE))
	{
		new_tok = (t_tree_token *)ft_malloc(sizeof(t_tree_token));
		new_tok->type = list->before->type;
		new_tok->value = list->before->value;
		add_next(tree->last_child, new_tok);
	}
}

void	parse_logical(t_token_list *list, t_tree *tree)
{
	t_tree_token	*new_tok;

	new_tok = (t_tree_token *)ft_malloc(sizeof(t_tree_token));
	if (sym_accept(list, LOGICAL_END) || sym_accept(list, LOGICAL_OR))
	{
		new_tok->type = list->before->type;
		new_tok->value = list->before->value;
		add_child(tree, new_tok);
	}
}

void	parse_pipe(t_token_list *list, t_tree *tree)
{
	t_tree_token	*new_tok;

	new_tok = (t_tree_token *)ft_malloc(sizeof(t_tree_token));
	if (sym_accept(list, PIPE))
	{
		new_tok->type = list->before->type;
		new_tok->value = list->before->value;
		add_next(tree->last_child, new_tok);
	}
	while (sym_accept(list, WORD) \
	|| sym_accept(list, SINGLE_QUOTE) \
	|| sym_accept(list, DOUBLE_QUOTE))
	{
		new_tok = (t_tree_token *)ft_malloc(sizeof(t_tree_token));
		new_tok->type = list->before->type;
		new_tok->value = list->before->value;
		add_next(tree->last_child, new_tok);
	}
}

void	parse_command(t_token_list *list, t_tree *tree)
{
	t_tree_token	*new_tok;

	new_tok = (t_tree_token *)ft_malloc(sizeof(t_tree_token));
	if (sym_accept(list, WORD))
	{
		new_tok->type = list->before->type;
		new_tok->value = list->before->value;
		add_child(tree, new_tok);
	}
	while (sym_accept(list, WORD) \
	|| sym_accept(list, SINGLE_QUOTE) \
	|| sym_accept(list, DOUBLE_QUOTE))
	{
		new_tok = (t_tree_token *)ft_malloc(sizeof(t_tree_token));
		new_tok->type = list->before->type;
		new_tok->value = list->before->value;
		add_next(tree->last_child, new_tok);
	}
}

void	parse_redir(t_token_list *list, t_tree *tree)
{
	t_tree_token	*new_tok;
	char			*err;

	new_tok = (t_tree_token *)ft_malloc(sizeof(t_tree_token));
	if (sym_accept(list, RIGHT_REDIR) \
	|| sym_accept(list, LEFT_REDIR) \
	|| sym_accept(list, RIGHT_APPEND) \
	|| sym_accept(list, LEFT_APPEND))
	{
		new_tok->type = list->before->type;
		new_tok->value = list->before->value;
		add_child(tree, new_tok);
	}
	if (sym_accept(list, WORD) \
	|| sym_accept(list, SINGLE_QUOTE) \
	|| sym_accept(list, DOUBLE_QUOTE))
	{
		new_tok = (t_tree_token *)ft_malloc(sizeof(t_tree_token));
		new_tok->type = list->before->type;
		new_tok->value = list->before->value;
		add_next(tree->last_child, new_tok);
	}
	else
	{
		err = type_to_string(list->cur->type);
		write(2, "bash: syntax error near unexpected token `", 43);
		write(2, err, ft_strlen(err));
		write(2, "\'\n", 2);
		exit(EXIT_FAILURE);
		return ; //syntax error
	}
}
