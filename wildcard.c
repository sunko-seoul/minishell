/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjunl <hyunjunl@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 18:55:37 by hyunjunl          #+#    #+#             */
/*   Updated: 2023/11/27 09:37:02 by hyunjunl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <dirent.h>
#include <stdlib.h>
#include "minishell.h"

static int	pattern_match(char *pattern, char *path)
{
	int	*dp[2];
	int	path_len;
	int	ret;
	int	i;

	path_len = ft_strlen(path);
	dp[0] = ft_calloc(path_len + 1, sizeof(int));
	dp[1] = ft_calloc(path_len + 1, sizeof(int));
	dp[1][0] = 1;
	while (*pattern)
	{
		ft_memcpy(dp[0], dp[1], (path_len + 1) * sizeof(int));
		dp[1][0] = (*pattern == '\32' && dp[0][0]);
		i = 0;
		while (++i <= path_len)
			dp[1][i] = ((*pattern == path[i - 1] && dp[0][i - 1])
					|| (*pattern == '\32'
						&& (dp[0][i - 1] || dp[0][i] || dp[1][i - 1])));
		++pattern;
	}
	ret = !dp[1][path_len];
	free(dp[0]);
	free(dp[1]);
	return (ret);
}

static void	iterate_dirent(char *pattern, DIR *dir, t_str_bldr *str_bldr)
{
	struct dirent	*entry;
	int				pattern_len;
	int				find_dir;

	pattern = ft_strdup(pattern);
	pattern_len = ft_strlen(pattern);
	find_dir = (pattern[pattern_len - 1] == '/');
	while (pattern[pattern_len - 1] == '/')
		pattern[--pattern_len] = '\0';
	entry = readdir(dir);
	while (entry)
	{
		if (!(entry->d_name[0] == '.' && pattern[0] != '.')
			&& !(find_dir && !is_directory(entry->d_name))
			&& pattern_match(pattern, entry->d_name) == 0)
		{
			append_str(str_bldr, entry->d_name, ft_strlen(entry->d_name));
			append_char(str_bldr, '\36');
		}
		entry = readdir(dir);
	}
	free(pattern);
}

char	*process_wildcard(char *pattern)
{
	DIR			*dir;
	t_str_bldr	str_bldr;

	if (ft_strchr(pattern, '\32') == 0)
		return (ft_strjoin(pattern, "\36"));
	init_str_bldr(&str_bldr);
	dir = opendir(".");
	if (dir)
		iterate_dirent(pattern, dir, &str_bldr);
	closedir(dir);
	if (str_bldr.sz == 0)
	{
		while (*pattern)
		{
			if (*pattern == '\32')
				append_char(&str_bldr, '*');
			else
				append_char(&str_bldr, *pattern);
			++pattern;
		}
		append_char(&str_bldr, '\36');
	}
	return (str_bldr.str);
}
