/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 22:35:30 by sunko             #+#    #+#             */
/*   Updated: 2023/07/28 23:03:01 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	arg_error(void)
{
	char	*shell_name;

	shell_name = get_shell_name();
	write(2, shell_name, ft_strlen(shell_name));
	write(2, ARG_ERROR, QUOTE_ERROR_LEN);
	exit(EXIT_FAILURE);
}

void	print_error(void)
{
	char	*shell_name;

	shell_name = get_shell_name();
	perror(shell_name);
	(void)shell_name;
	exit(EXIT_FAILURE);
}

void	quote_error(void)
{

	char	*shell_name;

	shell_name = get_shell_name();
	write(2, shell_name, ft_strlen(shell_name));
	write(2, QUOTE_ERROR, QUOTE_ERROR_LEN);
	exit(EXIT_FAILURE);
}
