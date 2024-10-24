/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjunl <hyunjunl@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 16:22:20 by hyunjunl          #+#    #+#             */
/*   Updated: 2023/11/26 08:33:55 by hyunjunl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include <unistd.h>
#include "minishell.h"

char	*get_env(t_env *env_lst, char *key)
{
	while (env_lst)
	{
		if (ft_strcmp(env_lst->key, key) == 0)
			return (env_lst->val);
		env_lst = env_lst->next;
	}
	return (0);
}

void	set_env(t_env **env_lst, char *key, char *val, int o_create)
{
	t_env	*node;

	node = *env_lst;
	while (node && ft_strcmp(node->key, key))
		node = node->next;
	if (node && val)
	{
		free(node->val);
		node->val = val;
		free(key);
	}
	else if (node == 0 && o_create)
	{
		node = ft_calloc(1, sizeof(t_env));
		node->key = key;
		node->val = val;
		node->next = *env_lst;
		*env_lst = node;
	}
	else
	{
		free(key);
		free(val);
	}
}

void	unset_env(t_env **env_lst, char *key)
{
	t_env	*node;
	t_env	*prev;

	node = *env_lst;
	prev = 0;
	while (node && ft_strcmp(node->key, key))
	{
		prev = node;
		node = node->next;
	}
	if (node == 0)
		return ;
	if (prev)
		prev->next = node->next;
	else
		*env_lst = node->next;
	free(node->key);
	free(node->val);
	free(node);
}

t_env	*create_env_lst(char **envp)
{
	t_env	*env_lst;
	char	*eq;
	int		i;

	env_lst = 0;
	i = 0;
	while (envp[i])
	{
		eq = ft_strchr(envp[i], '=');
		if (eq)
			set_env(&env_lst, ft_substr(envp[i], 0, eq - envp[i]),
				ft_strdup(eq + 1), 1);
		++i;
	}
	return (env_lst);
}

char	**create_env_arr(t_env *env_lst)
{
	char	**env_arr;
	t_env	*node;
	char	*tmp;
	int		i;

	node = env_lst;
	i = 0;
	while (env_lst)
	{
		if (env_lst->val)
			++i;
		env_lst = env_lst->next;
	}
	env_arr = ft_calloc(i + 1, sizeof(char *));
	while (node)
	{
		if (node->val)
		{
			tmp = ft_strjoin(node->key, "=");
			env_arr[--i] = ft_strjoin(tmp, node->val);
			free(tmp);
		}
		node = node->next;
	}
	return (env_arr);
}
