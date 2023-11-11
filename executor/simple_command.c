/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 10:22:34 by sunko             #+#    #+#             */
/*   Updated: 2023/11/11 21:36:17 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	insert_argument(t_simple_command *sim_cmd, char *argument)
{
	int		idx;
	size_t	arg_len;

	idx = sim_cmd->num_of_arg;
	arg_len = ft_strlen(argument);
	sim_cmd->args[idx] = (char *)ft_malloc(sizeof(char) * (arg_len + 1));
	ft_strlcpy(sim_cmd->args[idx], argument, arg_len + 1);
	sim_cmd->num_of_arg += 1;
}

t_simple_command	*create_simple_cmd(void)
{
	t_simple_command	*sim_cmd;

	sim_cmd = (t_simple_command *)ft_malloc(sizeof(t_simple_command));
	sim_cmd->max_available_arg = 20;
	sim_cmd->fd_in = 0;
	sim_cmd->fd_out = 1;
	sim_cmd->num_of_arg = 0;
	sim_cmd->args = (char **)\
	ft_malloc(sizeof(char *) * sim_cmd->max_available_arg);
	sim_cmd->inputfile = NULL;
	sim_cmd->outfile = NULL;
	return (sim_cmd);
}


