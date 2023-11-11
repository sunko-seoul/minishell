/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 21:18:41 by sunko             #+#    #+#             */
/*   Updated: 2023/11/11 21:47:30 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	change_fd(int old_fd, int new_fd)
{
	if (old_fd == new_fd)
		return ;
	if (dup2(old_fd, new_fd) == -1)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	close(old_fd);
}

void	create_fd_pipe(t_command *cmd)
{
	int	i;

	i = -1;
	cmd->fd_pipe = (int **)ft_malloc(sizeof(int *) * cmd->num_of_simple_cmd);
	while (++i < cmd->num_of_simple_cmd)
	{
		cmd->fd_pipe[i] = (int *)ft_malloc(sizeof(int) * 2);
		pipe(cmd->fd_pipe[i]);
	}
	return ;
}

void	set_out_file(t_command *cmd, int i)
{
	t_simple_command	*sim_cmd;

	sim_cmd = cmd->simple_commands[i];
	sim_cmd->fd_out = open(sim_cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (sim_cmd->fd_out == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
}

void	set_in_file(t_command *cmd, int i)
{
	t_simple_command	*sim_cmd;

	sim_cmd = cmd->simple_commands[i];
	sim_cmd->fd_in = open(sim_cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (sim_cmd->fd_in == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
}

void	set_io_fd(t_command *cmd)
{
	int	i;

	i = -1;
	if (cmd->num_of_simple_cmd == 1)
		return ;
	cmd->simple_commands[0]->fd_out = cmd->fd_pipe[0][1];
	while (++i < cmd->num_of_simple_cmd)
	{
		if (i == cmd->num_of_simple_cmd - 1) // last_command
		{
			if (cmd->simple_commands[i]->outfile)
				set_out_file(cmd, i);
			else
				change_fd(cmd->simple_commands[i]->fd_out, 1);
		}
		else
		{
			change_fd(cmd->simple_commands[i]->fd_in, cmd->fd_pipe[i][0]);
		}
	}
}
