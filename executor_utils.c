/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 01:21:19 by hyunjunl          #+#    #+#             */
/*   Updated: 2023/11/27 11:03:21 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include "minishell.h"

char	*get_cmd_path(t_cmd *cmd, t_sh_info *sh_info)
{
	char	**env_path;
	char	*cmd_path;
	char	*tmp_path;
	int		x_ok;

	if (ft_strchr(cmd->argv[0], '/'))
		return (ft_strdup(cmd->argv[0]));
	env_path = sh_info->path;
	cmd_path = 0;
	tmp_path = 0;
	x_ok = 0;
	while (env_path && *env_path && x_ok == 0)
	{
		tmp_path = ft_strjoin(*env_path++, cmd->argv[0]);
		if (access(tmp_path, F_OK) == 0 && !is_directory(tmp_path))
		{
			free(cmd_path);
			cmd_path = tmp_path;
			x_ok = (access(tmp_path, X_OK) == 0);
		}
		else
			free(tmp_path);
	}
	return (cmd_path);
}

int	redirect_input(t_cmd *cmd)
{
	int	ret;
	int	fd;

	if (cmd->in_file == 0)
		return (0);
	fd = open_file(cmd->in_file, O_RDONLY, 0);
	ret = (fd == -1 || dup2(fd, 0) == -1);
	close(fd);
	return (ret);
}

int	redirect_output(t_cmd *cmd)
{
	int	ret;
	int	fd;

	if (cmd->out_flag == ~0)
		return (1);
	else if (cmd->out_file == 0)
		return (0);
	fd = open_file(cmd->out_file, cmd->out_flag, 0);
	ret = (fd == -1 || dup2(fd, 1) == -1);
	close(fd);
	return (ret);
}

int	is_directory(char *path)
{
	struct stat	buf;

	return (stat(path, &buf) == 0 && (buf.st_mode & S_IFDIR));
}

int	(*get_builtin(char *cmd_name))(t_cmd *cmd, t_sh_info *sh_info)
{
	if (cmd_name == 0)
		return (0);
	else if (ft_strcmp(cmd_name, "echo") == 0)
		return (builtin_echo);
	else if (ft_strcmp(cmd_name, "cd") == 0)
		return (builtin_cd);
	else if (ft_strcmp(cmd_name, "pwd") == 0)
		return (builtin_pwd);
	else if (ft_strcmp(cmd_name, "export") == 0)
		return (builtin_export);
	else if (ft_strcmp(cmd_name, "unset") == 0)
		return (builtin_unset);
	else if (ft_strcmp(cmd_name, "env") == 0)
		return (builtin_env);
	else if (ft_strcmp(cmd_name, "exit") == 0)
		return (builtin_exit);
	else
		return (0);
}
