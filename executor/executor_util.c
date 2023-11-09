/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 00:05:51 by sunko             #+#    #+#             */
/*   Updated: 2023/11/10 00:08:50 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

char	**split_path(void)
{
	char	*path;
	char	**rst;

	path = getenv("PATH");
	if (!path)
	{
		printf("goto set path\n");
		exit(1);
	}
	rst = ft_split(path, ':');
	if (!rst)
	{
		printf("malloc error\n");
		exit(1);
	}
	return (rst);
}

char	*cmd_file_path(char *cmd)
{
	char	**path;
	char	*path_cmd;

	path = split_path();
	if (!ft_strnstr(cmd, "bin", ft_strlen(cmd)))
	path_cmd = join_binpath_cmd(path, cmd);
	return (path_cmd);
}


char	*join_binpath_cmd(char *path[], char *cmd)
{
	char	*cmd_path;
	char	*absolute_path;
	int		i;

	i = -1;
	while (path[++i])
	{
		cmd_path = ft_strjoin(path[i], "/");
		if (!cmd_path)
		{
			printf("malloc error\n");
			exit(1);
		}
		absolute_path = ft_strjoin(cmd_path, cmd);
		if (!absolute_path)
		{
			printf("malloc error\n");
			exit(1);
		}
		free(cmd_path);
		if (!access(absolute_path, F_OK))
			break ;
		free(absolute_path);
	}
	if (!path[i])
		printf("not found command %s\n", cmd);
	return (absolute_path);
}
