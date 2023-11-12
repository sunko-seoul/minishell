/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 10:36:49 by sunko             #+#    #+#             */
/*   Updated: 2023/11/13 00:56:04 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	insert_simple_cmd(t_command *cmd, t_simple_command *simple_cmd)
{
	cmd->simple_commands[++(cmd->idx)] = simple_cmd;
	cmd->num_of_simple_cmd++;
}

void	init_struct_cmd(t_command *cmd)
{
	cmd->max_available_simple_cmd = 20;
	cmd->num_of_simple_cmd = 0;
	cmd->idx = -1;
	cmd->simple_commands = (t_simple_command **)\
	ft_malloc(sizeof(t_simple_command *) * cmd->max_available_simple_cmd);
}
