/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symtab.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 21:43:29 by sunko             #+#    #+#             */
/*   Updated: 2023/11/13 22:48:30 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "symtab.h"

void	init_symtab(t_symtab_stack *symtab_stack)
{
	t_symtab	*global_symtab;

	symtab_stack->symtab_count = 1;
	global_symtab = (t_symtab *)ft_malloc(sizeof(t_symtab));
	ft_memset(global_symtab, 0, sizeof(t_symtab));
	symtab_stack->global_symtab = global_symtab;
	symtab_stack->local_symtab = global_symtab;
	symtab_stack->symtab_list[0] = global_symtab;
	global_symtab->level = 0;
}

char	*get_key(char *row, char *equal)
{
	int		len;
	char	*key;

	len = (int)(equal - row);
	key = (char *)ft_malloc(sizeof(char) * (len + 1));
	ft_strlcpy(key, row, len + 1);
	return (key);
}

t_symtab_entry	*do_lookup(char *str, t_symtab *symtab)
{
	t_symtab_entry	*entry;
	size_t			str_len;

	if (!str || !symtab)
		return (NULL);
	entry = symtab->first;
	str_len = ft_strlen(str);
	while (entry)
	{
		if (ft_strncmp(entry->name, str, str_len) == 0)
			return (entry);
		entry = entry->next;
	}
	return (NULL);
}

t_symtab_entry	*add_to_symtab(t_symtab_stack *sym_stack, char *symbol)
{
	t_symtab		*st;
	t_symtab_entry	*entry;
	size_t			symbol_len;

	if (!symbol || symbol[0] == '\0')
		return (NULL);
	symbol_len = ft_strlen(symbol);
	st = sym_stack->local_symtab;
	entry = do_lookup(symbol, st);
	if (entry)
		return (entry);
	entry = ft_malloc(sizeof(t_symtab_entry));
	ft_memset(entry, 0, sizeof(t_symtab_entry));
	entry->name = ft_malloc(sizeof(char) * (symbol_len + 1));
	strlcpy(entry->name, symbol, symbol_len);
	if (!st->first)
		st->first = entry;
	else
		st->last->next = entry;
	st->last = entry;
	return (entry);
}

void	symtab_entry_set_value(t_symtab_entry *entry, char *value)
{
	char	*new_value;
	size_t	val_len;

	if (entry->val)
		free(entry->val);
	if (!value)
	{
		entry->val = NULL;
		return ;
	}
	val_len = ft_strlen(value);
	new_value = ft_malloc(sizeof(char) * (val_len + 1));
	ft_strlcpy(new_value, value, val_len + 1);
	entry->val = new_value;
}


void	initsh(t_symtab_stack *symtab_stack, char *envp[])
{
	t_symtab_entry	*entry;
	char			**row;
	char			*equal;
	char			*key;

	init_symtab(symtab_stack);
	row = envp;
	while (*row)
	{
		equal = ft_strchr(*row, '=');
		if (equal)
		{
			key = get_key(*row, equal);
			entry = add_to_symtab(symtab_stack, key);
			if (entry)
				symtab_entry_set_value(entry, equal + 1);
		}
		else
			entry = add_to_symtab(symtab_stack, *row);
		row++;
	}
}


