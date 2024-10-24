/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjunl <hyunjunl@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 12:24:15 by hyunjunl          #+#    #+#             */
/*   Updated: 2023/11/26 08:36:39 by hyunjunl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include "minishell.h"

static char	*get_env_name(char *env)
{
	char	*end_ptr;

	end_ptr = env + 1;
	if (!(ft_isalpha(*end_ptr) || *end_ptr == '_'))
		return (0);
	while (ft_isalnum(*end_ptr) || *end_ptr == '_')
		++end_ptr;
	return (ft_substr(env, 1, end_ptr - env - 1));
}

static char	*expand_exit_status(t_sh_info *sh_info,
		t_str_bldr *str_bldr, char *word)
{
	char	*exit;

	exit = ft_itoa(sh_info->exit);
	append_str(str_bldr, exit, ft_strlen(exit));
	free(exit);
	return (word + 2);
}

char	*expand_env(t_sh_info *sh_info, t_str_bldr *str_bldr,
		char *word, int double_quote)
{
	char	*env_name;
	char	*env_val;

	if (*(word + 1) == '?')
		return (expand_exit_status(sh_info, str_bldr, word));
	env_name = get_env_name(word);
	if (env_name == 0)
	{
		append_char(str_bldr, '$');
		return (word + 1);
	}
	env_val = get_env(sh_info->env_lst, env_name);
	word += ft_strlen(env_name) + 1;
	free(env_name);
	while (env_val && *env_val)
	{
		if (double_quote || ft_strchr(" \t\n*", *env_val) == 0)
			append_char(str_bldr, *env_val);
		else if (*env_val == '*')
			append_char(str_bldr, '\32');
		else
			append_char(str_bldr, '\36');
		++env_val;
	}
	return (word);
}

static void	expand_env_vars(t_sh_info *sh_info,
		t_str_bldr *str_bldr, char *word)
{
	int		double_quote;
	char	*end_ptr;

	double_quote = 0;
	while (*word)
	{
		if (*word == '\"')
			double_quote ^= 1;
		else if (*word == '$')
			word = expand_env(sh_info, str_bldr, word, double_quote) - 1;
		else if (double_quote || ft_strchr("*\'", *word) == 0)
			append_char(str_bldr, *word);
		else if (*word == '*')
			append_char(str_bldr, '\32');
		else
		{
			end_ptr = ft_strchr(word + 1, '\'');
			append_str(str_bldr, word + 1, end_ptr - word - 1);
			word = end_ptr;
		}
		++word;
	}
}

char	**expand_word(t_sh_info *sh_info, char *word)
{
	char		**words;
	t_str_bldr	str_bldr;
	char		*str;
	int			i;

	init_str_bldr(&str_bldr);
	expand_env_vars(sh_info, &str_bldr, word);
	words = ft_split(str_bldr.str, "\36");
	free(str_bldr.str);
	init_str_bldr(&str_bldr);
	i = 0;
	while (words[i])
	{
		str = process_wildcard(words[i++]);
		append_str(&str_bldr, str, ft_strlen(str));
		free(str);
	}
	free_str_arr(words);
	words = ft_split(str_bldr.str, "\36");
	free(str_bldr.str);
	if (words[0] == 0 && (ft_strchr(word, '\'') || ft_strchr(word, '\"')))
		words[0] = ft_strdup("");
	return (words);
}
