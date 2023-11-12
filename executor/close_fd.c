/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 23:06:51 by sunko             #+#    #+#             */
/*   Updated: 2023/11/12 14:36:15 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	close_input_pipe(t_command *cmd, int idx)
{
	int		i;

	i = -1;
	while (++i < cmd->num_of_simple_cmd - 1)
	{
		if (idx == i + 1)
			dup2(cmd->fd_pipe[i][0], 0);
		close(cmd->fd_pipe[i][0]);
	}
}

void	close_output_pipe(t_command *cmd, int idx)
{
	int		i;

	i = -1;
	while (++i < cmd->num_of_simple_cmd - 1)
	{
		if (idx == i)
			dup2(cmd->fd_pipe[i][1], 1);
		close(cmd->fd_pipe[i][1]);
	}
}

void	close_input_fd(t_command *cmd, int idx)
{
	int					i;
	int					fd;
	t_simple_command	*s_cmd;

	s_cmd = cmd->simple_commands[idx];
	close_input_pipe(cmd, idx);
	if (cmd->simple_commands[idx]->infile)
	{
		fd = open(cmd->simple_commands[idx]->infile, O_RDONLY, 0644);
		dup2(fd, 0);
		close(fd);
	}
}

void	close_output_fd(t_command *cmd, int idx)
{
	int					i;
	int					fd;
	t_simple_command	*s_cmd;

	s_cmd = cmd->simple_commands[idx];
	close_output_pipe(cmd, idx);
	if (cmd->simple_commands[idx]->outfile)
	{
		fd = open(cmd->simple_commands[idx]->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		dup2(fd, 1);
		close(fd);
	}
}


void	close_not_use_fd(t_command *cmd, int idx)
{
	close_input_fd(cmd, idx);
	close_output_fd(cmd, idx);
}
