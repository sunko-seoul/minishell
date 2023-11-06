/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_type.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:26:05 by sunko             #+#    #+#             */
/*   Updated: 2023/11/06 15:45:22 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	tree_check_type(t_tree_token *tree_tok, t_token_type type)
{
	if (tree_tok->type == type)
		return (1);
	else
		return (0);
}

