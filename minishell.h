/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 22:11:19 by sunko             #+#    #+#             */
/*   Updated: 2023/10/29 14:50:32 by sunko            ###   ########.fr       */
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
# include "signal/signal.h"
# include "token/token.h"
# include "source.h"


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



void	*ft_malloc(size_t size);
char	*get_shell_name(void);
void	arg_error(void);
void	print_error(void);
void	quote_error(void);
char	*read_cmd(void);
void	*ft_realloc(void *ptr, size_t new_size);



#endif
