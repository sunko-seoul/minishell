/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 22:09:25 by sunko             #+#    #+#             */
/*   Updated: 2023/10/30 18:22:33 by sunko            ###   ########.fr       */
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
	//t_syntex_tree	*tree;

	skip_white_space(src);
	token_list = create_token_list();
	token_list = tokenizer(token_list, src);
	//tree = parser(token_list);


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

// t_syntex_tree	*parser(t_token_list *token_list)
// {
// 	(void *)token_list;
// 	return NULL;
// }
