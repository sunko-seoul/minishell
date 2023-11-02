/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 22:09:25 by sunko             #+#    #+#             */
/*   Updated: 2023/11/02 23:32:38 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_execute(t_source *src);
void			token_push_back(t_token_list *list, t_token *token);
t_token_list	*create_token_list(void);
size_t			find_close_quote(char *str);
t_token			*create_token(void);
size_t			find_next_space(char *str);
int	ft_is_not_word(char c);


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
	tree->before_child = NULL;
	tree->cur_child = NULL;
	parser(token_list, tree);
	return 0;
}

void	add_child(t_token_list *list, t_tree *tree, t_tree_token *new_tok)
{
	t_tree_token	*cur_tok;

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

void	add_next(t_token_list *list, t_tree_token *child_tok, t_tree_token *new_tok)
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
	{
		parse_redir(list, tree);
	}
}

void	parse_redir(t_token_list *list, t_tree *tree)
{
	t_tree_token	*new_tok;

	new_tok = (t_tree_token *)ft_malloc(sizeof(t_tree_token));

	if (sym_accept(list, RIGHT_REDIR) \
	|| sym_accept(list, LEFT_REDIR) \
	|| sym_accept(list, RIGHT_APPEND) \
	|| sym_accept(list, LEFT_APPEND))
	{
		new_tok->type = list->before->type;
		new_tok->value = list->before->value;
		add_child(list, tree, new_tok);
	}
	if (sym_accept(list, WORD))
	{
		new_tok = (t_tree_token *)ft_malloc(sizeof(t_tree_token));
		new_tok->type = list->before->type;
		new_tok->value = list->before->value;
		add_next(list, tree->last_child, new_tok);
	}
	else
		return ; //syntax error
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

