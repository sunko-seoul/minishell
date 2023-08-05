/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 22:09:25 by sunko             #+#    #+#             */
/*   Updated: 2023/08/05 14:40:57 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc , char *argv[])
{
	(void)argc;
	(void)argv;
	char		*command;
	t_termios	origin_attr;
	//t_token		*token_list;

	if (argc != 1)
		arg_error();
	disable_ctrl_c_output(&origin_attr);
	call_signal();
	while (1)
	{
		command = readline("minishell> ");
		if (!command)
			break;
		else if (command[0] == 0)
			;
		else
		{
			scan(command);
			printf("%s\n", command);
		}
		add_history(command);
	}
}

