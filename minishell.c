/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 08:32:03 by hyunjunl          #+#    #+#             */
/*   Updated: 2024/03/12 00:59:06 by hyunjunl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "minishell.h"

extern volatile sig_atomic_t	g_last_signal_num;

static void	free_all_token(t_token_lst *tok_lst)
{
	t_token	*next_tok;
	t_token	*cur_tok;

	cur_tok = tok_lst->head;
	while (cur_tok)
	{
		next_tok = cur_tok->next;
		if (cur_tok->value)
			free(cur_tok->value);
		free(cur_tok);
		cur_tok = next_tok;
	}
}

static t_tree_node	*parse_line(t_sh_info *sh_info, char *line)
{
	t_token_lst		tok_lst;
	t_token			*cur_tok;
	t_tree_node		*parse_tree;

	ft_bzero(&tok_lst, sizeof(t_token_lst));
	tokenize(&tok_lst, line);
	cur_tok = tok_lst.head;
	if (cur_tok == 0)
		return (0);
	parse_tree = parse_list(sh_info, &cur_tok);
	if (g_last_signal_num == SIGINT)
		sh_info->exit = 1;
	else if (cur_tok || parse_tree == 0)
	{
		if (cur_tok)
			print_syntax_error(cur_tok->value);
		else
			print_syntax_error(0);
		free_all_tree_node(parse_tree);
		parse_tree = 0;
		sh_info->exit = 258;
	}
	free_all_token(&tok_lst);
	return (parse_tree);
}

static char	*read_input(t_sh_info *sh_info)
{
	char	*line;

	g_last_signal_num = 0;
	line = readline("minishell$ \001\033[s\002");
	if (line == 0)
	{
		printf("\033[u\033[1B\033[1Aexit\n");
		exit(sh_info->exit);
	}
	if (g_last_signal_num == SIGINT)
	{
		sh_info->exit = 1;
		free(line);
		return (0);
	}
	if (*line)
		add_history(line);
	if (check_quote_error(line))
	{
		sh_info->exit = 258;
		free(line);
		return (0);
	}
	return (line);
}

int	main(int argc, char **argv, char **envp)
{
	t_sh_info	sh_info;
	char		*line;
	t_tree_node	*parse_tree;

	(void) argc;
	(void) argv;
	init_sh_info(&sh_info, envp);
	set_signal_handler();
	while (1)
	{
		line = read_input(&sh_info);
		if (line == 0)
			continue ;
		parse_tree = parse_line(&sh_info, line);
		if (parse_tree)
			traverse_node(parse_tree, &sh_info);
		free_all_tree_node(parse_tree);
		free(line);
	}
	return (0);
}
