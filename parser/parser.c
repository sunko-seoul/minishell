/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 16:32:04 by sunko             #+#    #+#             */
/*   Updated: 2023/10/31 23:01:43 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	next_sym(t_token_list *list)
{
	if (list->cur != list->tail)
	{
		list->before = list->cur;
		list->cur = list->cur->next;
	}
}

int	sym_accept(t_token_list *list, t_token_type type)
{
	if (list->cur->type == type)
	{
		next_sym(list);
		return (1);
	}
	return (0);
}

int	sym_expect(t_token_list *list, t_token_type type)
{
	if (sym_accept(list, type))
		return (1);
	perror("expect: unexpected symbol");
	return (0);
}
