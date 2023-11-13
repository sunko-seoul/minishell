/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symtab.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 21:21:30 by sunko             #+#    #+#             */
/*   Updated: 2023/11/13 23:14:57 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYMTAB_H
# define SYMTAB_H

# include "../minishell.h"
# define MAX_SYMTAB	256	/* maximum allowed symbol tables in the stack */

typedef struct s_symtab_entry
{
	char					*name;	/* key */
	char					*val;	/* value */
	struct s_symtab_entry	*next;
}	t_symtab_entry;

typedef struct s_symtab
{
	int				level;
	t_symtab_entry	*first;
	t_symtab_entry	*last;
}	t_symtab;

typedef struct s_symtab_stack
{
	int				symtab_count;
	t_symtab		*symtab_list[MAX_SYMTAB];
	t_symtab		*global_symtab;
	t_symtab		*local_symtab;
}	t_symtab_stack;


void			initsh(t_symtab_stack *symtab_stack, char *envp[]);
void			symtab_entry_set_value(t_symtab_entry *entry, char *value);
t_symtab_entry	*add_to_symtab(t_symtab_stack *sym_stack, char *symbol);
t_symtab_entry	*do_lookup(char *str, t_symtab *symtab);
char			*get_key(char *row, char *equal);
void			init_symtab(t_symtab_stack *symtab_stack);
void			free_symtab(t_symtab *symtab);

#endif
