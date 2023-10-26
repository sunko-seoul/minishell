/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 22:09:25 by sunko             #+#    #+#             */
/*   Updated: 2023/10/26 23:37:28 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token/token.h"

int main(int argc , char *argv[])
{
	char		*command;
	t_termios	origin_attr;
	t_source	src;
	//t_token		*token_list;

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
		printf("%s\n", command);
		init_src(command, &src);
		parse_execute(&src);
		add_history(command);
	}
	exit(EXIT_SUCCESS);
}

int	parse_execute(t_source *src)
{
	t_token_list	*token_list;

	skip_white_space(src);
	token_list = tokenizer(src);

}

t_token_list	*tokenizer(t_source *src)
{
	t_token_list	*token_list;
	t_token			*new_token;
	char			cur;
	char			next;
	int				idx;

	token_list = create_token_list();
	while (peek_char(src) != EOF)
	{
		cur = next_char(src);
		new_token = create_token();
		if (cur == '&')
		{
			next = peek_char(src);
			if (next != '&')
				continue ; // error?
			new_token->string = "&&";
			new_token->type = LOGICAL_END;
			next_char(src);
		}
		else if (cur == '|')
		{
			next = peek_char(src);
			if (next == '|')
			{
				new_token->string = "||";
				new_token->type = LOGICAL_OR;
				next_char(src);
			}
			else
			{
				new_token->string == "|";
				new_token->type = PIPE;
			}
		}
		else if (cur == '\'' || cur == '\"')
		{
			int i = 0;
			idx = find_close_quote(src->buffer + src->curpos);
			if (!idx)
				continue; // error handler
			new_token->string = (char *)malloc(sizeof(idx + 1));
			if (!new_token->string)
				continue; // error handler
			new_token->string[0] = cur;
			if (cur == '\'')
				new_token->type = SIGLE_QUOTE;
			else if (cur == '\"')
				new_token->type = DOUBLE_QUOTE;
			while (idx--)
				new_token->string[++i] = next_char(src);
		}
		else if (cur == '*')
		{
			new_token->string = "*";
			new_token->type = WILDCARD;
		}
		else if (cur == '<')
		{
			next = peek_char(src);
			if (next == '<')
			{
				new_token->string = "<<";
				new_token->type = RIGHT_APPEND;
				next_char(src);
			}
			else
			{
				new_token->string = "<";
				new_token->type = RIGHT_REDIR;
			}
		}
		else if (cur == '>')
		{
			next = peek_char(src);
			if (next == '<')
			{
				new_token->string = "<<";
				new_token->type = LEFT_APPEND;
				next_char(src);
			}
			else
			{
				new_token->string = "<";
				new_token->type = LEFT_REDIR;
			}
		}


	}
}

size_t	find_close_quote(char *str)
{
	char	quote;
	size_t	idx;
	size_t	len;

	quote = str[0];
	if (quote != '\'' && quote != '\"')
		return	(0);
	idx = 0;
	len = ft_strlen(str);
	while (++idx < len)
	{
		if (str[idx] == quote)
			return (idx);
	}
	return 0;
}



t_token	*create_token(void)
{
	t_token		*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	return new_token;
}

