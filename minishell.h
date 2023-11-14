/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 22:11:19 by sunko             #+#    #+#             */
/*   Updated: 2023/11/14 10:48:08 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define READLINE_LIBRARY
# define SUNKO_PC
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/ioctl.h>
# include <errno.h>
# include <curses.h>
# include "libft/libft.h"
# include "terminal/terminal.h"
# include "parser/parser.h"
# include "signal/signal.h"
# include "token/source.h"
# include "token/token.h"
# include "util/util.h"
# include "executor/executor.h"
# include "symtab/symtab.h"
# include "builtins/builtins.h"


# if defined (SUNKO_PC)
#  include "/Users/sunko/.brew/opt/readline/include/readline/readline.h"
#  include "/Users/sunko/.brew/opt/readline/include/readline/history.h"
# else
#  include "/Users/hyunjoo/.brew/opt/readline/include/readline/readline.h"
#  include "/Users/hyunjoo/.brew/opt/readline/include/readline/history.h"
# endif

# define ARG_ERROR			": Too many arguments\n"
# define ARG_ERROR_LEN		22
# define QUOTE_ERROR		": Not interpret unclose quote\n"
# define QUOTE_ERROR_LEN	31
# define MAX_TOKEN			17

void	arg_error(void);
void	print_error(void);
void	quote_error(void);


int		check_next_type(t_token_list *token_list, t_token_type type);
int		check_cur_type(t_token_list *token_list, t_token_type type);
char	*type_to_string(t_token_type type);

/* debug tool */
int		parse_execute(t_source *src, char *envp[]);
void	token_debug(t_token_list *token_list);
void	tree_debug(t_tree *tree);
void	syntax_error(t_token_type type);

#endif
