/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_scan.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 23:27:46 by sunko             #+#    #+#             */
/*   Updated: 2023/08/05 12:35:54 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

int	get_quote_len(char *string, char quote)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (string[++i] != quote)
		len++;
	return (len);
}

char	*quote_malloc(int len)
{
	char	*result;

	result = (char *)malloc(sizeof(char) * len + 1);
	if (result == NULL)
		print_error();
	result[len] = 0;
	return (result);
}

void	sigle_quote_scan(t_token_list *list, char *command, size_t *i)
{
	t_node	*new_node;
	int		quote_len;

	new_node = create_node();
	quote_len = get_quote_len(&(command[*i]), '\'');
	new_node->token->string = quote_malloc(quote_len);
	ft_strlcpy(new_node->token->string, &(command[*i + 1]), quote_len + 1);
	new_node->token->type = SIGLE_QUOTE;
	*i += quote_len + 1;
	push_back(list, new_node);
}

void	double_quote_scan(t_token_list *list, char *command, size_t *i)
{
	t_node	*new_node;
	int		quote_len;

	new_node = create_node();
	quote_len = get_quote_len(&(command[*i]), '\"');
	new_node->token->string = quote_malloc(quote_len);
	ft_strlcpy(new_node->token->string, &(command[*i + 1]), quote_len + 1);
	new_node->token->type = SIGLE_QUOTE;
	*i += quote_len + 1;
	push_back(list, new_node);
}
