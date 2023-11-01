/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 22:09:25 by sunko             #+#    #+#             */
/*   Updated: 2023/11/01 16:48:54 by sunko            ###   ########.fr       */
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
	t_syntax_tree	tree;

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
			printf("        %s    \n", token_list->cur->string);
			token_list->cur = token_list->cur->next;
		}
		token_list->cur = token_list->head;
	}
	print_hello();
	tree = parser(token_list);
	return 0;
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

// char	*push_cur_token(t_token_list *list, t_token_type type)
// {
// 	char	*cur;

// 	cur = NULL;
// 	if (check_cur_type(list, type))
// 	{
// 		cur = list->cur->string;
// 		if (list->cur != list->tail)
// 			list->cur = list->cur->next;
// 		return cur;
// 	}
// 	return NULL;
// }


t_syntax_tree	parser(t_token_list *token_list)
{
	t_syntax_tree	tree;

	printf("parser call\n");
	tree.list = parse_list(token_list);
	printf("parser end\n");
	return (tree);
}

t_m_list	parse_list(t_token_list *list)
{
	t_m_list	new_list;

	printf("parse_list call\n");
	new_list.pipeline = parse_pipeline(list);
	if (sym_accept(list, LOGICAL_END) || sym_accept(list, LOGICAL_OR))
	{
		new_list.logical_operator = list->before->string;
		parse_list(list);
	}
	printf("parse_list end\n");
	return (new_list);
}

t_pipeline	parse_pipeline(t_token_list *list)
{
	t_pipeline	pipe_line;

	printf("pipeline call\n");
	pipe_line.is_pipeline = 0;
	pipe_line.next = NULL;
	pipe_line.command = parse_command(list);
	if (check_cur_type(list, WORD))
	{
		pipe_line.next = (t_pipeline *)ft_malloc(sizeof(t_pipeline));
		pipe_line.next->command = parse_command(list);
	}
	if (sym_accept(list, PIPE))
		pipe_line.is_pipeline = 1;
	if (pipe_line.is_pipeline)
		parse_pipeline(list);
	printf("pipeline end\n");
	return (pipe_line);
}

t_command	parse_command(t_token_list *list)
{
	t_command	command;

	printf("parse_command call\n");
	if (check_cur_type(list, WORD))
		command.is_simple = 1;
	else
		command.is_simple = 0;
	if (command.is_simple)
		command.u_command.simple_command = parse_simple_cmd(list);
	else
		command.u_command.redirect_list = parse_redir_list(list);
	printf("parse_command end\n");
	return (command);
}

t_simple_command	parse_simple_cmd(t_token_list *token_list)
{
	t_simple_command	simple_cmd;

	printf("parse_simple_cmd call\n");
	simple_cmd.element = parse_simple_cmd_element(token_list);
	printf("parse_simple_cmd end\n");
	return (simple_cmd);
}

t_simple_command_element	*parse_simple_cmd_element(t_token_list *list)
{
	t_simple_command_element	*element;

	printf("parse_simple_cmd_element call\n");
	element = (t_simple_command_element *)ft_malloc(sizeof(t_simple_command_element));
	if (check_cur_type(list, RIGHT_APPEND) \
	|| check_cur_type(list, LEFT_APPEND) \
	|| check_cur_type(list, RIGHT_REDIR) \
	|| check_cur_type(list, LEFT_REDIR))
	{
		element->u_element.redirection = parse_redir(list);
	}
	else if (check_cur_type(list, WORD))
		element->u_element.word = parse_word(list);
	printf("parse_simple_cmd_element end\n");
	return (element);
}

t_redirect_list	parse_redir_list(t_token_list *list)
{
	t_redirect_list	redir_list;

	printf("parse_redir_list call\n");
	redir_list.redirection = parse_redir(list);
	redir_list.next = NULL;
	while (check_cur_type(list, RIGHT_APPEND) \
	|| check_cur_type(list, LEFT_APPEND) \
	|| check_cur_type(list, RIGHT_REDIR) \
	|| check_cur_type(list, LEFT_REDIR))
	{
		redir_list.next = (t_redirect_list *)ft_malloc(sizeof(t_redirect_list));
		*redir_list.next = parse_redir_list(list);
	}
	printf("parse_redir_list end\n");
	return (redir_list);
}

t_redirect	parse_redir(t_token_list *list)
{
	t_redirect	redir;

	printf("parse_redir call\n");
	if (sym_accept(list, WORD))
		redir.fd_num = ft_atoi(list->before->string);
	else
		redir.fd_num = 0;
	if (sym_accept(list, RIGHT_REDIR) \
	|| sym_accept(list, LEFT_REDIR) \
	|| sym_accept(list, RIGHT_APPEND) \
	|| sym_accept(list, LEFT_APPEND))
		redir.type = list->before->string;
	redir.word = parse_word(list);
	printf("parse_redir end\n");
	return (redir);
}

t_word	parse_word(t_token_list *list)
{
	t_word	word;

	word.word = 0;
	printf("parse_word call\n");
	if (sym_accept(list, WORD))
	{
		word.word = list->before->string;
	}
	return (word);
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

