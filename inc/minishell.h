/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmunoz <gmunoz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 16:33:48 by guido             #+#    #+#             */
/*   Updated: 2025/07/15 23:04:16 by gmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# ifndef ECHOCTL
#  define ECHOCTL 0000100
# endif

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <dirent.h>
# include <termios.h>
# include <limits.h>
# include "libft.h"
# include "tokenizing.h"
# include "parsing.h"

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef enum e_err_msg
{
	ERRMSG_CMD_NOT_FOUND,
	ERRMSG_NO_SUCH_FILE,
	ERRMSG_PERM_DENIED,
	ERRMSG_AMBIGUOUS,
	ERRMSG_TOO_MANY_ARGS,
	ERRMSG_NUMERIC_REQUI
}	t_err_msg;

typedef enum e_err_no
{
	ENO_SUCCESS,
	ENO_GENERAL,
	ENO_CANT_EXEC = 126,
	ENO_NOT_FOUND,
	ENO_EXEC_255 = 255
}	t_err_no;

typedef enum e_ast_direction
{
	TD_LEFT,
	TD_RIGHT
}	t_ast_direction;

typedef struct s_err
{
	t_err_no	no;
	t_err_msg	msg;
	char		*cause;
}	t_err;

typedef struct s_path
{
	t_err	err;
	char	*path;
}	t_path;

typedef struct s_minishell
{
	char			*line;
	t_token			*tokens;
	t_token			*curr_token;
	t_node			*ast;
	int				exit_s;
	bool			signint_child;
	t_parse_err		parse_err;
	int				stdin;
	int				stdout;
	char			**environ;
	t_env			*envlst;
	bool			heredoc_sigint;
	struct termios	original_term;
}	t_minishell;

extern t_minishell	g_minishell;

int			main(int argc, char **argv, char **env);
void		*lst_mng(void *ptr, bool clean);
void		init_signals(void);
void		sigquit_handler(int sig);
char		*ft_strjoin_f(char *s1, char *s2);
void		init_tree(t_node *node);
char		**expand(char *str);
char		*handle_squotes(char *str, size_t *i);
char		*handle_dquotes(char *str, size_t *i);
char		*handle_dollar(char *str, size_t *i);
char		*handle_normal_str(char *str, size_t *i);
bool		is_valid_var_char(char c);
char		*get_envlst_val(char *key);
char		*clean_empty_strs(char *str);
char		**expander_split(char const *s);
char		**globber(char **expanded);
size_t		str_arr_len(char **str_arr);
size_t		match_counter(char *pattern);
bool		match_star(char *pattern, char *str);
bool		contains_asterisk(char *str);
char		**join_str_arrs(char ***str_arrs);
char		*strip_quotes(char *str);
bool		is_delimiter(char *delimiter, char *str);
void		heredoc_expander(char *str, int fd);
void		clean_ms(void);
int			exec_node(t_node *tree, bool piped);
int			err_msg(t_err err);
int			ft_out(t_io_node *io_list, int *status);
int			ft_in(t_io_node *io_list, int *status);
int			ft_append(t_io_node *io_list, int *status);
t_err		check_write(char *file);
t_err		check_exec(char *file, bool cmd);
t_err		check_read(char *file);
bool		is_builtin(char *arg);
int			exec_builtin(char **args);
void		update_env_list(char *key, char *value, bool create);
int			ft_echo(char **args);
int			ft_env(void);
int			ft_cd(char *path);
int			ft_pwd(void);
int			ft_export(char **argv);
int			ft_unset(char **args);
void		ft_exit(char **args);
char		*get_key(char *str);
char		*get_value(char *str);
bool		env_entry_exists(char *key);
int			check_key(char *str);
t_path		get_path(char *cmd);
int			get_exit_status(int status);
void		init_env_list(void);
int			exec_simple_cmd(t_node *node, bool piped);

#endif