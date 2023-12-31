/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 22:11:19 by sunko             #+#    #+#             */
/*   Updated: 2023/11/01 15:50:55 by sunko            ###   ########.fr       */
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


int	check_next_type(t_token_list *token_list, t_token_type type);
int	check_cur_type(t_token_list *token_list, t_token_type type);
t_syntax_tree	parser(t_token_list *token_list);
t_m_list	parse_list(t_token_list *list);
t_pipeline	parse_pipeline(t_token_list *list);
t_command	parse_command(t_token_list *list);
t_simple_command	parse_simple_cmd(t_token_list *token_list);
t_simple_command_element	*parse_simple_cmd_element(t_token_list *list);
t_redirect_list	parse_redir_list(t_token_list *list);
t_redirect	parse_redir(t_token_list *list);
t_word	parse_word(t_token_list *list);
char	*type_to_string(t_token_type type);

#endif
