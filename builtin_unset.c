/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjunl <hyunjunl@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 21:53:02 by hyunjunl          #+#    #+#             */
/*   Updated: 2023/11/27 14:36:04 by hyunjunl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static int	unset_name(t_sh_info *sh_info, char *name)
{
	if (!is_valid_identifier(name))
		return (1);
	unset_env(&sh_info->env_lst, name);
	if (ft_strcmp(name, "PATH") == 0)
		update_path(sh_info);
	return (0);
}

int	builtin_unset(t_cmd *cmd, t_sh_info *sh_info)
{
	char	**argv;
	int		err;

	argv = cmd->argv + 1;
	err = 0;
	while (*argv)
	{
		if (unset_name(sh_info, *argv))
		{
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(*argv, 2);
			ft_putendl_fd("': not a valid identifier", 2);
			err = 1;
		}
		++argv;
	}
	return (err);
}
