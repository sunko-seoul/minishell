/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 23:34:06 by sunko             #+#    #+#             */
/*   Updated: 2023/08/04 15:17:01 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

void	init_token(t_token *token_list)
{
	int		i;

	i = -1;
	while (++i < TOKEN_NUM)
		token_list[i].type = i;
	token_list[0].string = "&&";
	token_list[1].string = "||";
	token_list[2].string = "*";
	token_list[3].string = "\'";
	token_list[4].string = "\"";
	token_list[5].string = "|";
	token_list[6].string = "(";
	token_list[7].string = ")";
	token_list[8].string = "{";
	token_list[9].string = "}";
	token_list[10].string = "[";
	token_list[11].string = "]";
	token_list[12].string = ";";
	token_list[13].string = ">";
	token_list[14].string = "<";
	token_list[15].string = ">>";
	token_list[16].string = "<<";
	token_list[17].string = "$";
}
