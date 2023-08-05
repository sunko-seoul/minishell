/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 22:38:43 by sunko             #+#    #+#             */
/*   Updated: 2023/07/28 22:42:50 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERMINAL_H
# define TERMINAL_H

# include "../minishell.h"
# include <termios.h>
# include <term.h>

typedef struct termios t_termios;

void	disable_ctrl_c_output(t_termios *origin_attr);

#endif
