/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 13:59:25 by sunko             #+#    #+#             */
/*   Updated: 2023/11/11 21:24:27 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "../minishell.h"

typedef struct s_simple_command
{
	int		max_available_arg;
	int		num_of_arg;
	int		fd_in;
	int		fd_out;
	char	*outfile;
	char	*inputfile;
	char	**args;
}	t_simple_command;

typedef struct s_command
{
	int					max_available_simple_cmd;
	int					num_of_simple_cmd;
	int					idx;
	int					**fd_pipe;
	t_simple_command	**simple_commands;
}	t_command;

/* executor_util.c */
char				**split_path(void);
char				*join_binpath_cmd(char *path[], char *cmd);
char				*cmd_file_path(char *cmd);

/* executor.c */
void				executor_value(t_tree_token *node, t_command *cmd);
void				insert_list_argument(t_tree_token *node, t_command *cmd);
void				executor_traversal(t_tree_token *node, t_command *cmd);
void				executor(t_tree *tree, char *envp[]);

/* simple_command.c */
void				insert_argument(t_simple_command *sim_cmd, char *argument);
t_simple_command	*create_simple_cmd(void);
void				insert_simple_cmd(t_command *cmd, t_simple_command *simple_cmd);

/* command.c */
void				init_struct_cmd(t_command *cmd);
void				insert_list_argument(t_tree_token *node, t_command *cmd);

/* fd.c */
void				change_fd(int old_fd, int new_fd);
void				create_fd_pipe(t_command *cmd);

#endif
