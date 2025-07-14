/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmunoz <gmunoz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 16:33:48 by guido             #+#    #+#             */
/*   Updated: 2025/07/14 22:45:47 by gmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#ifndef ECHOCTL
#define ECHOCTL 0000100
#endif

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

int		main(int argc, char **argv, char **env);
void	init_minishell(char **env);
void	*lst_mng(void *ptr, bool clean);
void	init_signals(void);
void	sigquit_handler(int sig);
void	sigint_handler(int sig);
char	*ft_strjoin_f(char *s1, char *s2);
void	init_tree(t_node *node);
char	**expand(char *str);
char	*handle_squotes(char *str, size_t *i);
char	*handle_dquotes(char *str, size_t *i);
char	*handle_dollar(char *str, size_t *i);
char	*handle_normal_str(char *str, size_t *i);
bool	is_valid_var_char(char c);
char	*get_envlst_val(char *key);
char	*clean_empty_strs(char *str);
char	**expander_split(char const *s);
char	**globber(char **expanded);
size_t	str_arr_len(char **str_arr);
size_t	match_counter(char *pattern);
bool	match_star(char *pattern, char *str);
bool	contains_asterisk(char *str);
char	**join_str_arrs(char ***str_arrs);
char	*strip_quotes(char *str);
bool	is_delimiter(char *delimiter, char *str);
void	heredoc_expander(char *str, int fd);
void	*garbage_collector(void *ptr, bool clean);
void	clean_ms(void);

#endif