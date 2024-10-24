/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjunl <hyunjunl@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 21:53:02 by hyunjunl          #+#    #+#             */
/*   Updated: 2023/11/27 09:25:11 by hyunjunl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <stdlib.h>
#include "minishell.h"

static int	count_env(t_env *env_lst)
{
	int	cnt;

	cnt = 0;
	while (env_lst)
	{
		++cnt;
		env_lst = env_lst->next;
	}
	return (cnt);
}

static int	display_min_env(t_env *env_lst, int *used)
{
	t_env	*min_env;
	int		min_idx;
	int		i;

	min_env = 0;
	min_idx = -1;
	i = 0;
	while (env_lst)
	{
		if (!used[i] && (min_env == 0
				|| ft_strcmp(min_env->key, env_lst->key) > 0))
		{
			min_env = env_lst;
			min_idx = i;
		}
		env_lst = env_lst->next;
		++i;
	}
	if (min_idx == -1)
		return (-1);
	printf("declare -x %s", min_env->key);
	if (min_env->val)
		printf("=\"%s\"", min_env->val);
	printf("\n");
	return (min_idx);
}

static int	display_env(t_env *env_lst)
{
	int	*used;
	int	idx;

	used = ft_calloc(count_env(env_lst), sizeof(int));
	while (1)
	{
		idx = display_min_env(env_lst, used);
		if (idx == -1)
			break ;
		used[idx] = 1;
	}
	free(used);
	return (0);
}

static int	export_name(t_sh_info *sh_info, char *name)
{
	char	*key;
	char	*val;
	char	*eq;

	eq = ft_strchr(name, '=');
	if (eq)
		key = ft_substr(name, 0, eq - name);
	else
		key = ft_strdup(name);
	if (!is_valid_identifier(key))
	{
		free(key);
		return (1);
	}
	if (eq)
		val = ft_strdup(eq + 1);
	else
		val = 0;
	set_env(&sh_info->env_lst, key, val, 1);
	if (ft_strcmp(key, "PATH") == 0)
		update_path(sh_info);
	return (0);
}

int	builtin_export(t_cmd *cmd, t_sh_info *sh_info)
{
	char	**argv;
	int		err;

	argv = cmd->argv + 1;
	if (*argv == 0)
		return (display_env(sh_info->env_lst));
	err = 0;
	while (*argv)
	{
		if (export_name(sh_info, *argv))
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(*argv, 2);
			ft_putendl_fd("': not a valid identifier", 2);
			err = 1;
		}
		++argv;
	}
	return (err);
}
