/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjunl <hyunjunl@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 21:11:54 by hyunjunl          #+#    #+#             */
/*   Updated: 2023/11/26 08:37:09 by hyunjunl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "minishell.h"

void	free_str_arr(char **str_arr)
{
	size_t	i;

	if (str_arr == 0)
		return ;
	i = 0;
	while (str_arr[i])
		free(str_arr[i++]);
	free(str_arr);
}

void	add_slash_to_paths(char **path)
{
	char	*tmp;

	if (path == 0)
		return ;
	while (*path)
	{
		if ((*path)[ft_strlen(*path) - 1] != '/')
		{
			tmp = *path;
			*path = ft_strjoin(*path, "/");
			free(tmp);
		}
		++path;
	}
}

void	update_path(t_sh_info *sh_info)
{
	free_str_arr(sh_info->path);
	sh_info->path = ft_split(get_env(sh_info->env_lst, "PATH"), ":");
	add_slash_to_paths(sh_info->path);
}

int	is_valid_identifier(char *str)
{
	if (str == 0 || !(ft_isalpha(*str) || *str == '_'))
		return (0);
	++str;
	while (ft_isalnum(*str) || *str == '_')
		++str;
	if (*str)
		return (0);
	return (1);
}

int	open_file(const char *path, int oflag, int print_err)
{
	int	fd;

	fd = open(path, oflag, 0644);
	if (fd == -1 && print_err)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(path);
	}
	return (fd);
}
