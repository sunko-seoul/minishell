/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 14:00:14 by sunko             #+#    #+#             */
/*   Updated: 2023/11/05 14:01:14 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	executor(t_tree *tree, char *envp[])
{
	t_tree_token	*cur;
	char			**path;
	char			*path_cmd;
	char			**cmd_arg;
	int				cnt;
	int				i;

	path = split_path();
	// redirection
	// command
	// pipe

	// command
	cur = tree->first_child;
	cnt = 0;
	i = -1;
	while (cur)
	{
		if (cur == tree->last_child && cur->type == WORD)
		{
			if (!ft_strnstr(cur->value, "bin", ft_strlen(cur->value)))
				path_cmd = join_binpath_cmd(path, cur->value);
			else
				path_cmd = cur->value;
		}
		else if (cur->type == WORD)
			cnt++;
		cur = cur->next;
	}
	cmd_arg = (char **)ft_malloc(sizeof(char *) * (cnt + 1));
	cur = tree->last_child;
	while (cur)
	{
		if (cur == tree->last_child)
		{
			cur = cur->next;
			continue;
		}
		else
			cmd_arg[++i] = cur->value;
		cur = cur->next;
	}
	cmd_arg[++i] = NULL;
	execve(path_cmd, cmd_arg, envp);
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
