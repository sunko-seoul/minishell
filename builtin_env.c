/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjunl <hyunjunl@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 17:55:42 by hyunjunl          #+#    #+#             */
/*   Updated: 2023/11/27 09:24:46 by hyunjunl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include "minishell.h"

static void	display_env(t_env *env_lst)
{
	if (env_lst == 0)
		return ;
	display_env(env_lst->next);
	if (env_lst->val == 0)
		return ;
	printf("%s=%s\n", env_lst->key, env_lst->val);
}

int	builtin_env(t_cmd *cmd, t_sh_info *sh_info)
{
	(void) cmd;
	display_env(sh_info->env_lst);
	return (0);
}
