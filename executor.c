/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjunl <hyunjunl@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 21:08:51 by hyunjunl          #+#    #+#             */
/*   Updated: 2024/06/06 17:00:47 by hyunjunl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include "minishell.h"

extern volatile sig_atomic_t	g_last_signal_num;

static void	execute_single_builtin(t_cmd *cmd, t_sh_info *sh_info)
{
	int	std_in;
	int	std_out;

	std_in = dup(0);
	std_out = dup(1);
	if (redirect_input(cmd) || redirect_output(cmd))
		sh_info->exit = 1;
	else
		sh_info->exit = get_builtin(cmd->argv[0])(cmd, sh_info);
	dup2(std_in, 0);
	dup2(std_out, 1);
	close(std_in);
	close(std_out);
}

static void	execute_cmd(t_cmd *cmd, t_sh_info *sh_info)
{
	char	*cmd_path;

	if (cmd->argv[0] == 0)
		exit(0);
	cmd_path = get_cmd_path(cmd, sh_info);
	if (cmd_path && access(cmd_path, X_OK) == 0 && !is_directory(cmd_path))
	{
		execve(cmd_path, cmd->argv, create_env_arr(sh_info->env_lst));
		perror("minishell: execve");
		exit(1);
	}
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd->argv[0], 2);
	ft_putstr_fd(": ", 2);
	if (cmd_path == 0)
		ft_putendl_fd("command not found", 2);
	else if (is_directory(cmd_path))
		ft_putendl_fd("is a directory", 2);
	else
		perror("");
	if (cmd_path && access(cmd_path, F_OK) == 0)
		exit(126);
	else
		exit(127);
}

static pid_t	fork_process(t_cmd *cmd, t_sh_info *sh_info,
		int in_fd, int pipe_fd[2])
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (redirect_input(cmd)
			|| (cmd->in_file == 0 && dup2(in_fd, 0) == -1)
			|| redirect_output(cmd)
			|| (cmd->out_file == 0 && dup2(pipe_fd[1], 1) == -1))
			exit(1);
		close(in_fd);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		if (get_builtin(cmd->argv[0]))
			exit(get_builtin(cmd->argv[0])(cmd, sh_info));
		else
			execute_cmd(cmd, sh_info);
	}
	return (pid);
}

static pid_t	handle_pipe(t_cmd *cmd_lst, t_sh_info *sh_info)
{
	pid_t	last;
	int		in_fd;
	int		pipe_fd[2];

	pipe_fd[0] = dup(0);
	while (cmd_lst)
	{
		in_fd = pipe_fd[0];
		pipe_fd[0] = -1;
		pipe_fd[1] = -1;
		if (cmd_lst->next)
			pipe(pipe_fd);
		else
			pipe_fd[1] = dup(1);
		last = fork_process(cmd_lst, sh_info, in_fd, pipe_fd);
		close(in_fd);
		close(pipe_fd[1]);
		cmd_lst = cmd_lst->next;
	}
	return (last);
}

void	execute_cmds(t_cmd *cmd_lst, t_sh_info *sh_info)
{
	pid_t	last;
	pid_t	pid;
	int		wstatus;

	if (cmd_lst == 0)
		return ;
	else if (cmd_lst->next == 0 && get_builtin(cmd_lst->argv[0]))
		return (execute_single_builtin(cmd_lst, sh_info));
	last = handle_pipe(cmd_lst, sh_info);
	sh_info->exit = 256;
	while (1)
	{
		pid = wait(&wstatus);
		if (pid == -1)
			break ;
		else if (pid == last)
			sh_info->exit = wstatus;
	}
	if (sh_info->exit & 127)
	{
		sh_info->exit = 128 | (sh_info->exit & 127);
		printf("\n");
	}
	else
		sh_info->exit >>= 8;
}
