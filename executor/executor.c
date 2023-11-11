/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 14:00:14 by sunko             #+#    #+#             */
/*   Updated: 2023/11/11 17:01:54 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	executor_value(t_tree_token *node, t_command *cmd)
{
	t_simple_command	*sim_cmd;
	int					i;

	if (!node)
		return ;
	if (node->type == CMD)
	{
		sim_cmd = create_simple_cmd();
		insert_simple_cmd(cmd, sim_cmd);
		return ;
	}
	if (node->is_list == 0)
	{
		if (node->type == CMD_VALUE)
			insert_argument(cmd->simple_commands[cmd->idx], node->u_value.value);
		if (node->type == REDIRECT)
		{
			if (node->left->tok_type == LEFT_REDIR || node->left->tok_type == LEFT_APPEND)
				cmd->simple_commands[cmd->idx]->inputfile = node->right->u_value.value;
			else if (node->left->tok_type == RIGHT_REDIR || node->left->tok_type == RIGHT_APPEND)
				cmd->simple_commands[cmd->idx]->outfile = node->right->u_value.value;
		}
	}
	if (node->is_list == 1)
		insert_list_argument(node, cmd);
}

void	insert_list_argument(t_tree_token *node, t_command *cmd)
{
	int		i;

	i = -1;
	while (node->u_value.list[++i])
		insert_argument(cmd->simple_commands[cmd->idx], node->u_value.list[i]);
}

void	executor_traversal(t_tree_token *node, t_command *cmd)
{
	if (!node)
		return ;
	executor_value(node, cmd);
	if (node->left)
		executor_traversal(node->left, cmd);
	if (node->right)
		executor_traversal(node->right, cmd);
}

void	command_debug(t_tree *tree, t_command cmd)
{
	printf("\n========= command ==========\n");
	for (int i = 0; i < cmd.num_of_simple_cmd; ++i)
	{
		printf("%d simple command = ", i + 1);
		printf("(infile = %s), ", cmd.simple_commands[i]->inputfile);
		printf("(outfile = %s), ", cmd.simple_commands[i]->outfile);
		printf("(argument = ");
		for (int j = 0; j < cmd.simple_commands[i]->num_of_arg; ++j)
			printf("%s, ", cmd.simple_commands[i]->args[j]);
		printf(")\n");
	}
}

void	execute(t_command *cmd, char **envp)
{
	int		i;
	int		tmp_in;
	int		tmp_out;
	int		fd_in;
	int		fd_out;
	int		fd_pipe[2];
	pid_t	pid;

	i = 0;
	tmp_in = dup(0);
	tmp_out = dup(1);
	while (i < cmd->num_of_simple_cmd)
	{
		if (cmd->simple_commands[i]->inputfile)
			fd_in = open(cmd->simple_commands[i]->inputfile, O_RDONLY, 0644);
		else
			fd_in = dup(tmp_in);
		dup2(fd_in, 0);
		close(fd_in);
		if (i == cmd->num_of_simple_cmd - 1)
		{
			if (cmd->simple_commands[i]->outfile)
				fd_out = open(cmd->simple_commands[i]->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			else
				fd_out = dup(tmp_out);
		}
		else
		{
			pipe(fd_pipe);
			fd_out = fd_pipe[1];
			fd_in = fd_pipe[0];
		}
		dup2(fd_out, 1);
		close(fd_out);
		pid = fork();
		if (pid == 0)
		{
			execve(cmd->simple_commands[i]->args[0], &(cmd->simple_commands[i]->args[1]), envp);
			perror("execve");
			exit(EXIT_FAILURE);
		}
		dup2(tmp_in, 0);
		dup2(tmp_out, 1);
		close(tmp_in);
		close(tmp_out);
		i++;
	}
	i = 0;
	waitpid(0, NULL, 0);
}

void	executor(t_tree *tree, char *envp[])
{
	t_command			cmd;

	init_struct_cmd(&cmd);
	executor_traversal(tree->root, &cmd);
	command_debug(tree, cmd);
	printf("\n================= execute ==================\n");
	execute(&cmd, envp);
}

