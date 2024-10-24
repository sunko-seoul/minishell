/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjunl <hyunjunl@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 21:07:42 by hyunjunl          #+#    #+#             */
/*   Updated: 2023/11/27 09:25:51 by hyunjunl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "minishell.h"

static char	**get_cdpath(char *dir, t_env *env_lst)
{
	char	**cdpath;

	if (dir[0] == '/' || ft_strcmp(dir, ".") == 0
		|| ft_strncmp(dir, "./", 2) == 0
		|| ft_strcmp(dir, "..") == 0
		|| ft_strncmp(dir, "../", 3) == 0)
		return (0);
	cdpath = ft_split(get_env(env_lst, "CDPATH"), ":");
	add_slash_to_paths(cdpath);
	return (cdpath);
}

static int	use_cdpath(char *dir, t_env *env_lst)
{
	char	**cdpath;
	char	*tmp;
	int		res;
	int		i;

	cdpath = get_cdpath(dir, env_lst);
	res = 0;
	i = 0;
	while (cdpath && cdpath[i] && res == 0)
	{
		tmp = ft_strjoin(cdpath[i], dir);
		res = (chdir(tmp) == 0);
		free(tmp);
		++i;
	}
	free_str_arr(cdpath);
	if (res == 0)
		return (1);
	tmp = getcwd(0, 0);
	printf("%s\n", tmp);
	free(tmp);
	return (0);
}

static char	*get_pwd(char *oldpwd, char *dir)
{
	char	*pwd;

	pwd = getcwd(0, 0);
	if (pwd)
		return (pwd);
	perror("cd: error retrieving current directory: "
		"getcwd: cannot access parent directories");
	if (oldpwd[ft_strlen(oldpwd) - 1] == '/')
		return (ft_strjoin(oldpwd, dir));
	oldpwd = ft_strjoin(oldpwd, "/");
	pwd = ft_strjoin(oldpwd, dir);
	free(oldpwd);
	return (pwd);
}

int	builtin_cd(t_cmd *cmd, t_sh_info *sh_info)
{
	char	*dir;

	dir = cmd->argv[1];
	if (dir == 0)
		dir = get_env(sh_info->env_lst, "HOME");
	if (dir == 0)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return (1);
	}
	if (*dir == '\0')
		dir = sh_info->pwd;
	if (use_cdpath(dir, sh_info->env_lst) && chdir(dir))
	{
		ft_putstr_fd("minishell: cd: ", 2);
		perror(dir);
		return (1);
	}
	set_env(&sh_info->env_lst, ft_strdup("OLDPWD"), sh_info->pwd, 0);
	sh_info->pwd = get_pwd(sh_info->pwd, dir);
	set_env(&sh_info->env_lst, ft_strdup("PWD"), ft_strdup(sh_info->pwd), 0);
	return (0);
}
