/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 22:09:25 by sunko             #+#    #+#             */
/*   Updated: 2023/10/31 12:17:08 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token/token.h"
#include "parser/parser.h"

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

int	parse_execute(t_source *src)
{
	t_token_list	*token_list;
	t_syntax_tree	tree;

	skip_white_space(src);
	token_list = create_token_list();
	token_list = tokenizer(token_list, src);
	tree = parser(token_list);


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
	}
	return 0;
}

t_syntax_tree	parser(t_token_list *token_list)
{
	t_syntax_tree	tree;

	tree.list = parse_list(token_list);
	return (tree);
}

t_m_list	parse_list(t_token_list *token_list)
{
	t_m_list	list;

	list.pipeline = parse_pipeline(token_list);
	// list->logical_operator
	// list->next
	return (list);
}

t_pipeline	parse_pipeline(t_token_list *token_list)
{
	t_pipeline	pipe_line;

	pipe_line.command = parse_command(token_list);
	//pipe_line->next
	//is_pipeline
	return (pipe_line);
}

t_command	parse_command(t_token_list *token_list)
{
	t_command	command;

	//is_siple
	if (command.is_simple)
		command.u_command.simple_command = parse_simple_cmd(token_list);
	else
		command.u_command.redirect_list = parse_redir_list(token_list);
	return (command);
}

t_simple_command	parse_simple_cmd(t_token_list *token_list)
{
	t_simple_command	simple_cmd;

	simple_cmd.element = parse_simple_cmd_element(token_list, &simple_cmd.num_elements);
	return (simple_cmd);
}

t_redirect_list	parse_redir_list(t_token_list *token_list)
{
	t_redirect_list	redir_list;

	return (redir_list);
}



