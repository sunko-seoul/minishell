/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sh_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjunl <hyunjunl@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 08:08:58 by hyunjunl          #+#    #+#             */
/*   Updated: 2023/11/26 08:36:52 by hyunjunl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
#include "minishell.h"

static void	init_shlvl(t_sh_info *sh_info)
{
	char	*shlvl;
	int		num;

	shlvl = get_env(sh_info->env_lst, "SHLVL");
	if (shlvl)
	{
		num = ft_atoll(shlvl, 0) + 1;
		if (num > 1000)
			num = 1;
		else if (num < 0)
			num = 0;
	}
	else
		num = 1;
	set_env(&sh_info->env_lst, ft_strdup("SHLVL"), ft_itoa(num), 1);
}

static void	init_env_lst(t_sh_info *sh_info, char **envp)
{
	sh_info->env_lst = create_env_lst(envp);
	unset_env(&sh_info->env_lst, "OLDPWD");
	set_env(&sh_info->env_lst, ft_strdup("OLDPWD"), 0, 1);
	set_env(&sh_info->env_lst, ft_strdup("PWD"), ft_strdup(sh_info->pwd), 1);
	init_shlvl(sh_info);
}

void	init_sh_info(t_sh_info *sh_info, char **envp)
{
	sh_info->pwd = getcwd(0, 0);
	if (sh_info->pwd == 0)
		sh_info->pwd = ft_strdup("/");
	init_env_lst(sh_info, envp);
	sh_info->path = 0;
	update_path(sh_info);
	if (sh_info->path == 0)
	{
		sh_info->path = ft_split("/usr/local/bin:/usr/local/sbin:"
				"/usr/bin:/usr/sbin:/bin:/sbin", ":");
		add_slash_to_paths(sh_info->path);
	}
	sh_info->exit = 0;
}
