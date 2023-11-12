/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 23:06:51 by sunko             #+#    #+#             */
/*   Updated: 2023/11/12 12:59:51 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	close_input_fd(t_command *cmd, int idx)
{
	int					i;
	t_simple_command	*s_cmd;

	i = 0;
	printf("\nclose_input_fd call (%d)\n", idx);
	s_cmd = cmd->simple_commands[idx];
	if (idx == 0)
	{
		if (s_cmd->inputfile)
		{
			s_cmd->fd_in = open(s_cmd->inputfile, O_RDONLY, 0644);
			dup2(s_cmd->fd_in, 0);
			close(s_cmd->fd_in);
		}
	}
	while (++i < cmd->num_of_simple_cmd)
	{
		if (idx == i)
		{
			if (s_cmd->inputfile)
			{
				s_cmd->fd_in = open(s_cmd->inputfile, O_RDONLY, 0644);
				dup2(s_cmd->fd_in, 0);
				close(s_cmd->fd_in);
			}
			else
			{
				printf("(%d) dup pipe[%d][0] -> 0\n", idx, idx - 1);
				dup2(cmd->fd_pipe[idx - 1][0], 0);
			}
		}
		printf("(%d) close pipe[%d][0]\n", idx, i - 1);
		close(cmd->fd_pipe[i - 1][0]);
	}
	printf("close_input_fd return (%d)\n", idx);
}

void	close_output_fd(t_command *cmd, int idx)
{
	int					i;
	t_simple_command	*s_cmd;

	i = -1;
	printf("\nclose_output_fd call (%d)\n", idx);
	s_cmd = cmd->simple_commands[idx];
	if (idx == cmd->num_of_simple_cmd - 1)
	{
		if (s_cmd->outfile)
		{
			s_cmd->fd_out = open(s_cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			dup2(s_cmd->fd_out, 1);
			close(s_cmd->fd_out);
		}
	}
	while (++i < cmd->num_of_simple_cmd - 1)
	{
		if (idx == i)
		{
			if (s_cmd->outfile)
			{
				s_cmd->fd_out = open(s_cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
				dup2(s_cmd->fd_out, 1);
				close(s_cmd->fd_out);
			}
			else
			{
				printf("(%d) dup pipe[%d][1] -> 1\n", idx, i);
				dup2(cmd->fd_pipe[i][1], 1);
			}
		}
		printf("(%d) close pipe[%d][1]\n", idx, i);
		close(cmd->fd_pipe[i][1]);
	}
	printf("close_output_fd return (%d)\n", idx);
}


void	close_not_use_fd(t_command *cmd, int idx)
{
	close_input_fd(cmd, idx);
	close_output_fd(cmd, idx);
}
