/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 08:32:31 by hyunjunl          #+#    #+#             */
/*   Updated: 2023/11/27 14:19:05 by hyunjunl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"

typedef enum e_token_type
{
	T_LOGICAL_AND,
	T_LOGICAL_OR,
	T_APPEND,
	T_HEREDOC,
	T_PIPE,
	T_OPEN_BRAKET,
	T_CLOSE_BRAKET,
	T_OUT_REDIR,
	T_IN_REDIR,
	T_AMPERSAND,
	T_WORD
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_token_lst
{
	t_token	*head;
	t_token	*tail;
}	t_token_lst;

typedef enum e_tree_node_type
{
	TN_LOGICAL_AND,
	TN_LOGICAL_OR,
	TN_APPEND,
	TN_HEREDOC,
	TN_LIST,
	TN_EXPR,
	TN_CMD,
	TN_OUT_REDIR,
	TN_IN_REDIR,
	TN_IO_REDIR,
	TN_CMD_ELEM,
	TN_WORD
}	t_tree_node_type;

typedef struct s_tree_node
{
	t_tree_node_type	type;
	char				*value;
	struct s_tree_node	*sibling;
	struct s_tree_node	*child;
}	t_tree_node;

typedef struct s_env
{
	char			*key;
	char			*val;
	struct s_env	*next;
}	t_env;

typedef struct s_sh_info
{
	t_env	*env_lst;
	char	*pwd;
	char	**path;
	int		exit;
}	t_sh_info;

typedef struct s_cmd
{
	char			**argv;
	char			*in_file;
	char			*out_file;
	int				out_flag;
	struct s_cmd	*next;
}	t_cmd;

/* tokenizer.c */
void		tokenize(t_token_lst *tok_list, char *line);

/* parser.c */
t_tree_node	*parse_list(t_sh_info *sh_info, t_token **tok_cur);

/* parser_utils.c */
void		free_all_tree_node(t_tree_node *root);
int			expect_type(t_token **cur, t_token_type type);
t_tree_node	*push_back_sibling(t_tree_node *first, t_tree_node *last);
t_tree_node	*create_parent_tree_node(t_tree_node_type type, t_tree_node *child);
t_tree_node	*create_tree_node(t_tree_node_type type, char *value);

/* init_sh_info.c */
void		init_sh_info(t_sh_info *sh_info, char **envp);

/* heredoc.c */
int			process_heredoc(t_sh_info *sh_info, t_tree_node *heredoc_node);

/* traverse_node.c */
void		traverse_node(t_tree_node *tree_node, t_sh_info *sh_info);

/* traverse_node_utils.c */
int			collect_io_info(t_tree_node *io_redir_child,
				t_cmd *cmd, t_sh_info *sh_info);
char		**join_argv(char **argv1, char **argv2);
void		free_cmd_lst(t_cmd *cmd_lst);

/* expansion.c */
char		**expand_word(t_sh_info *sh_info, char *word);
char		*expand_env(t_sh_info *sh_info, t_str_bldr *str_bldr,
				char *word, int double_quote);

/* executor.c */
void		execute_cmds(t_cmd *cmd_lst, t_sh_info *sh_info);

/* executor_utils.c */
char		*get_cmd_path(t_cmd *cmd, t_sh_info *sh_info);
int			redirect_input(t_cmd *cmd);
int			redirect_output(t_cmd *cmd);
int			is_directory(char *path);
int			(*get_builtin(char *cmd_name))(t_cmd *cmd, t_sh_info *sh_info);

/* minishell_utils.c */
void		free_str_arr(char **str_arr);
void		add_slash_to_paths(char **path);
void		update_path(t_sh_info *sh_info);
int			is_valid_identifier(char *str);
int			open_file(const char *path, int oflag, int print_err);

/* syntax.c */
void		print_syntax_error(char *str);
int			check_quote_error(char *line);

/* wildcard.c */
char		*process_wildcard(char *pattern);

/* signal.c */
void		set_signal_handler(void);

/* env.c */
char		*get_env(t_env *env_lst, char *key);
void		set_env(t_env **env_lst, char *key, char *val, int o_create);
void		unset_env(t_env **env_lst, char *key);
t_env		*create_env_lst(char **envp);
char		**create_env_arr(t_env *env_lst);

/* builtin_*.c */
int			builtin_echo(t_cmd *cmd, t_sh_info *sh_info);
int			builtin_cd(t_cmd *cmd, t_sh_info *sh_info);
int			builtin_pwd(t_cmd *cmd, t_sh_info *sh_info);
int			builtin_export(t_cmd *cmd, t_sh_info *sh_info);
int			builtin_unset(t_cmd *cmd, t_sh_info *sh_info);
int			builtin_env(t_cmd *cmd, t_sh_info *sh_info);
int			builtin_exit(t_cmd *cmd, t_sh_info *sh_info);

#endif
