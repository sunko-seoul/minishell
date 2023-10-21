/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 00:05:07 by sunko             #+#    #+#             */
/*   Updated: 2023/10/21 16:48:43 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "token.h"

void	right_redir_scan(t_token_list *list, char *command, size_t *i);
void	left_redir_scan(t_token_list *list, char *command, size_t *i);

t_token	scan(char *command)
{
	t_token			*token_sample;
	t_token_list	*token_list;
	size_t			len;
	size_t			i;
	size_t			j;

	token_sample = create_token_sample();
	token_list = create_token_list();
	len = ft_strlen(command);
	i = 0;
	while (i < len)
	{
		j = 0;
		while (j < TOKEN_NUM)
		{
			if (command[i] == token_sample[j].string[0])
			{
				if (j == SIGLE_QUOTE)
					sigle_quote_scan(token_list, command, &i);
				else if (j == DOUBLE_QUOTE)
					double_quote_scan(token_list, command, &i);
				else if (j == RIGHT_REDIR)
					right_redir_scan(token_list, command, &i);
				else if (j == LEFT_REDIR)
					left_redir_scan(token_list, command, &i);
				break;
			}
			j++;
		}
		printf("idx = %zu, command[i] = %c\n", i, command[i]);
		i++;
	}
	i = 0;
	while (token_list->cur != NULL)
	{
		printf("index %zu, string = %s, type = %u\n", i, token_list->cur->token->string, token_list->cur->token->type);
		token_list->cur = token_list->cur->next;
		i++;
	}
	return (*token_sample);
}

void	right_redir_scan(t_token_list *list, char *command, size_t *i)
{
	t_node	*new_node;
	size_t	temp_idx;

	new_node = create_node();
	push_back(list, new_node);
	temp_idx = *i;
	if (command[temp_idx + 1] == '>')
	{
		*i += 2;
		if (command[temp_idx + 2] == '\0')
			write(2, "bash: syntax error near unexpected token `newline'\n", 52);
		else if (command[temp_idx + 2] != ' ')
		{
			write(2, "bash: syntax error near unexpected token \'", 42);
			write(2, &(command[temp_idx + 2]), 1);
			write(2, "\'\n", 2);
		}
		else
		{
			new_node->token->type = RIGHT_APPEND;
			new_node->token->string = ">>";
		}
		return ;
	}
	new_node->token->type = RIGHT_REDIR;
	new_node->token->string = ">";
	*i += 1;
}

void	left_redir_scan(t_token_list *list, char *command, size_t *i)
{
	t_node	*new_node;
	size_t	temp_idx;

	new_node = create_node();
	push_back(list, new_node);
	temp_idx = *i;
	if (command[temp_idx + 1] == '<')
	{
		*i += 2;
		if (command[temp_idx + 2] == '\0')
			write(2, "bash: syntax error near unexpected token `newline'\n", 52);
		else if (command[temp_idx + 2] != ' ')
		{
			write(2, "bash: syntax error near unexpected token \'", 42);
			write(2, &(command[temp_idx + 2]), 1);
			write(2, "\'\n", 2);
		}
		else
		{
			new_node->token->type = LEFT_APPEND;
			new_node->token->string = "<<";
		}
		return ;
	}
	new_node->token->type = LEFT_REDIR;
	new_node->token->string = "<";
	*i += 1;
}
