/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 21:18:41 by sunko             #+#    #+#             */
/*   Updated: 2023/11/12 12:51:17 by sunko            ###   ########.fr       */
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
	cmd->fd_pipe = (int **)ft_malloc(sizeof(int *) * (cmd->num_of_simple_cmd - 1));
	while (++i < cmd->num_of_simple_cmd - 1)
	{
		cmd->fd_pipe[i] = (int *)ft_malloc(sizeof(int) * 2);
		pipe(cmd->fd_pipe[i]);
	}
	return ;
}
