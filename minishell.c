/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 22:09:25 by sunko             #+#    #+#             */
/*   Updated: 2023/11/04 14:37:22 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tree	*parser(t_token_list *list, t_tree *tree);
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
	/* token debug */
	token_debug(token_list);

	tree = (t_tree *)ft_malloc(sizeof(t_tree));
	tree->root = NULL;
	tree->first_child = NULL;
	tree->last_child = NULL;
	tree = parser(token_list, tree);

	/* tree debug */
	tree_debug(tree);
	return 0;
}

t_tree	*parser(t_token_list *list, t_tree *tree)
{
	while (list->cur)
	{
		if (check_cur_type(list, RIGHT_REDIR) \
		|| check_cur_type(list, LEFT_REDIR) \
		|| check_cur_type(list, RIGHT_APPEND) \
		|| check_cur_type(list, LEFT_APPEND))
			parse_redir(list, tree);
		if (check_cur_type(list, WORD))
			parse_command(list, tree);
		if (check_cur_type(list, PIPE))
			parse_pipe(list, tree);
		if (check_cur_type(list, LOGICAL_END) || check_cur_type(list, LOGICAL_OR))
			parse_logical(list, tree);
		if (check_cur_type(list, SINGLE_QUOTE) || check_cur_type(list, DOUBLE_QUOTE))
			parse_quote(list, tree);
		if (check_cur_type(list, LEFT_PAREN))
			parse_paren(list, tree);
	}
	return (tree);
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

