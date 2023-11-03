/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 22:09:25 by sunko             #+#    #+#             */
/*   Updated: 2023/11/03 19:42:08 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_child(t_tree *tree, t_tree_token *new_tok);
void	add_next(t_tree_token *child_tok, t_tree_token *new_tok);
t_tree	*parser(t_token_list *list, t_tree *tree);
void	parse_command(t_token_list *list, t_tree *tree);
void	parse_redir(t_token_list *list, t_tree *tree);
int		check_next_type(t_token_list *token_list, t_token_type type);
int		check_cur_type(t_token_list *token_list, t_token_type type);
char	*type_to_string(t_token_type type);

int main(int argc , char *argv[])
{
	char		*command;
	t_termios	origin_attr;
	t_source	src;
	(void)argc;
	(void)argv;

	if (argc != 1)
		arg_error();
	disable_ctrl_c_output(&origin_attr);
	call_signal();
	while (1)
	{
		command = readline("minishell > ");
		if (!command)
			exit(EXIT_SUCCESS);
		else if (command[0] == 0)
		{
			free(command);
			continue;
		}
		else if (ft_strncmp("exit", command, 5) == 0)
		{
			free(command);
			break;
		}
		init_src(command, &src);
		parse_execute(&src);
		add_history(command);
	}
	exit(EXIT_SUCCESS);
}

void	print_hello(void)
{
	return ;
}

int	parse_execute(t_source *src)
{
	t_token_list	*token_list;
	t_tree			*tree;

	skip_white_space(src);
	token_list = create_token_list();
	token_list = tokenizer(token_list, src);

	// print debug tool
	if (true)
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
	tree = (t_tree *)ft_malloc(sizeof(t_tree));
	tree->root = NULL;
	tree->first_child = NULL;
	tree->last_child = NULL;
	tree = parser(token_list, tree);
	tree->cur = tree->first_child;
	t_tree_token	*cur_child;
	cur_child = tree->first_child;
	while (cur_child)
	{
		tree->cur = cur_child;
		while (tree->cur)
		{
			printf("%s\n", tree->cur->value);
			tree->cur = tree->cur->next;
		}
		cur_child = cur_child->child;
	}
	return 0;
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

t_tree	*parser(t_token_list *list, t_tree *tree)
{
	if (check_cur_type(list, RIGHT_REDIR) \
	|| check_cur_type(list, LEFT_REDIR) \
	|| check_cur_type(list, RIGHT_APPEND) \
	|| check_cur_type(list, LEFT_APPEND))
		parse_redir(list, tree);
	if (check_cur_type(list, WORD))
		parse_command(list, tree);
	return (tree);
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
	while (sym_accept(list, WORD))
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
	if (sym_accept(list, WORD))
	{
		new_tok = (t_tree_token *)ft_malloc(sizeof(t_tree_token));
		new_tok->type = list->before->type;
		new_tok->value = list->before->value;
		printf("new_tok->value = %s\n", new_tok->value);
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

int	check_next_type(t_token_list *token_list, t_token_type type)
{
	if (!token_list->cur)
		return (-1);
	if (token_list->cur == token_list->tail)
		return (-1);
	if (token_list->cur->next->type == type)
		return (1);
	else
		return (0);
}

int	check_cur_type(t_token_list *token_list, t_token_type type)
{
	if (!token_list->cur)
		return (0);
	if (token_list->cur->type == type)
		return (1);
	else
		return (0);
}

char	*type_to_string(t_token_type type)
{
	if (type == LOGICAL_END)
		return "&&";
	else if (type == LOGICAL_OR)
		return "||";
	else if (type == WILDCARD)
		return "*";
	else if (type == SINGLE_QUOTE)
		return "'";
	else if (type == DOUBLE_QUOTE)
		return "\"";
	else if (type == PIPE)
		return "|";
	else if (type == LEFT_PAREN)
		return "(";
	else if (type == RIGHT_PAREN)
		return ")";
	else if (type == RIGHT_REDIR)
		return ">";
	else if (type == LEFT_REDIR)
		return "<";
	else if (type == RIGHT_APPEND)
		return ">>";
	else if (type == LEFT_APPEND)
		return "<<";
	else if (type == DOLLAR_SIGN)
		return "$";
	return NULL;
}

