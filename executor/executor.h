/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 13:59:25 by sunko             #+#    #+#             */
/*   Updated: 2023/11/09 10:43:19 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "../minishell.h"

char	*join_binpath_cmd(char *path[], char *cmd);
char	*cmd_file_path(char *cmd);
void	executor(t_tree *tree, char *envp[]);

typedef struct s_simple_command
{
	int		max_available_arg;
	int		num_of_arg;
	char	**args;
	// SimpleCommand();
	// void insert_argument(char *argument);
}	t_simple_command;

typedef struct s_command
{
	int					max_available_simple_cmd;
	int					num_of_simple_cmd;
	t_simple_command	**simple_commands;
	char				*outfile;
	char				*inputfile;
	// Command();
	// void insert_simple_command(simple_command *simple_command);
}	t_command;

void				insert_argument(t_simple_command *sim_cmd, char *argument);
t_simple_command	*create_simple_cmd(void);

#endif
