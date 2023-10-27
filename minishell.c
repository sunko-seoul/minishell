/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 22:09:25 by sunko             #+#    #+#             */
/*   Updated: 2023/10/27 12:07:42 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token/token.h"

int	parse_execute(t_source *src);
t_token_list	*tokenizer(t_source *src);
void			token_push_back(t_token_list *list, t_token *token);
t_token_list	*create_token_list(void);
size_t			find_close_quote(char *str);
t_token			*create_token(void);
size_t			find_next_space(char *str);


int main(int argc , char *argv[])
{
	char		*command;
	t_termios	origin_attr;
	t_source	src;
	//t_token		*token_list;
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

	skip_white_space(src);
	token_list = tokenizer(src);
	token_list->cur = token_list->head;
	while (token_list->cur != NULL)
	{
		printf("token->string = %s\n", token_list->cur->string);
		printf("token->type = %d\n", token_list->cur->type);
		token_list->cur = token_list->cur->next;
	}
	return 0;
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
		new_token->next = NULL;
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
				new_token->string = "|";
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
		else if (cur == '(')
		{
			new_token->string = "(";
			new_token->type = LEFT_PAREN;
		}
		else if (cur == ')')
		{
			new_token->string = ")";
			new_token->type = RIGHT_PAREN;
		}
		else
		{
			size_t	word_idx = 0;
			int	word_size = 0;
			new_token->type = WORD;
			word_size = find_next_space(src->buffer + src->curpos);
			new_token->string = (char *)malloc(sizeof(char) * word_size + 1);
			new_token->string[0] = cur;
			while (word_size--)
				new_token->string[++word_idx] = next_char(src);
			new_token->string[word_idx] = '\0';

		}
		token_push_back(token_list, new_token);
	}
	return token_list;
}

void	token_push_back(t_token_list *list, t_token *token)
{
	list->num_of_data += 1;
	if (list->head == NULL)
	{
		list->head = token;
		list->tail = token;
	}
	else
	{
		list->cur = list->head;
		while (list->cur->next != NULL)
			list->cur = list->cur->next;
		list->cur->next = token;
		list->tail = token;
	}
}

t_token_list	*create_token_list(void)
{
	t_token_list	*new_list;

	new_list = (t_token_list *)malloc(sizeof(t_token_list));
	if (!new_list)
		return (NULL);
	new_list->cur = NULL;
	new_list->head = NULL;
	new_list->tail = NULL;
	new_list->num_of_data = 0;
	return (new_list);
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

size_t	find_next_space(char *str)
{
	size_t	idx;

	idx = 0;
	while (str[idx] != ' ' && str[idx] != 0)
		idx++;
	return idx;
}



t_token	*create_token(void)
{
	t_token		*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	return new_token;
}

