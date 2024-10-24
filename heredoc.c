/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 23:41:44 by hyunjunl          #+#    #+#             */
/*   Updated: 2024/03/12 00:59:44 by hyunjunl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <unistd.h>
#include "minishell.h"

extern volatile sig_atomic_t	g_last_signal_num;

static char	*get_heredoc_file_name(void)
{
	const char *const	heredoc_prefix = "/tmp/sh-thd-";
	static int			heredoc_idx;
	char				*file_name;
	char				*idx_str;

	idx_str = ft_itoa(heredoc_idx++);
	file_name = ft_strjoin(heredoc_prefix, idx_str);
	free(idx_str);
	return (file_name);
}

static char	*remove_quote(char *word)
{
	t_str_bldr	str_bldr;
	char		*end_ptr;

	init_str_bldr(&str_bldr);
	while (*word)
	{
		if (*word == '\'' || *word == '\"')
		{
			end_ptr = ft_strchr(word + 1, *word);
			append_str(&str_bldr, word + 1, end_ptr - word - 1);
			word = end_ptr + 1;
		}
		else
			append_char(&str_bldr, *word++);
	}
	return (str_bldr.str);
}

static char	*read_input(t_sh_info *sh_info, char *delimiter, int quoted)
{
	char		*line;
	char		*line_ptr;
	t_str_bldr	str_bldr;

	line = readline("> \001\033[s\002");
	if (line == 0 || ft_strcmp(line, delimiter) == 0
		|| g_last_signal_num == SIGINT)
	{
		if (line == 0)
			ft_putstr_fd("\033[u\033[1B\033[1A", 1);
		free(line);
		return (0);
	}
	init_str_bldr(&str_bldr);
	line_ptr = line;
	while (*line_ptr)
	{
		if (!quoted && *line_ptr == '$')
			line_ptr = expand_env(sh_info, &str_bldr, line_ptr, 1);
		else
			append_char(&str_bldr, *line_ptr++);
	}
	free(line);
	return (str_bldr.str);
}

int	process_heredoc(t_sh_info *sh_info, t_tree_node *heredoc_node)
{
	char		*delimiter;
	int			quoted;
	int			fd;
	char		*line;

	delimiter = heredoc_node->value;
	quoted = (ft_strchr(delimiter, '\'') || ft_strchr(delimiter, '\"'));
	delimiter = remove_quote(delimiter);
	free(heredoc_node->value);
	heredoc_node->value = get_heredoc_file_name();
	fd = open_file(heredoc_node->value, O_WRONLY | O_CREAT | O_TRUNC, 0);
	while (1)
	{
		g_last_signal_num = 0;
		line = read_input(sh_info, delimiter, quoted);
		if (line == 0)
			break ;
		ft_putendl_fd(line, fd);
		free(line);
	}
	close(fd);
	free(delimiter);
	return (g_last_signal_num == SIGINT);
}
