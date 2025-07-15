/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmunoz <gmunoz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 20:15:49 by guido             #+#    #+#             */
/*   Updated: 2025/07/15 23:23:35 by gmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

typedef enum e_node_type
{
	N_PIPE,
	N_AND,
	N_OR,
	N_CMD
}	t_node_type;

typedef enum e_io_type
{
	IO_IN,
	IO_OUT,
	IO_HEREDOC,
	IO_APPEND
}	t_io_type;

typedef enum e_parse_err_type
{
	E_MEM = 1,
	E_SYNTAX
}	t_parse_err_type;

typedef struct s_io_node
{
	t_io_type			type;
	char				*value;
	char				**expanded_value;
	int					here_doc;
	struct s_io_node	*prev;
	struct s_io_node	*next;
}	t_io_node;

typedef struct s_node
{
	t_node_type			type;
	t_io_node			*io_list;
	char				*args;
	char				**expanded_args;
	struct s_node		*left;
	struct s_node		*right;
}	t_node;

typedef struct s_parse_err
{
	t_parse_err_type	type;
	char				*str;
}	t_parse_err;

t_node		*ft_parse(void);
void		set_parse_err(t_parse_err_type type);
void		get_next_token(void);
bool		curr_token_is_bin(void);
t_node		*term(void);
int			curr_token_prec(void);
int			prec(t_token_type type);
t_node		*new_node(t_node_type type);
t_node_type	get_node_type(t_token_type type);
void		clear_ast(t_node **ast);
void		clear_cmd_node(t_node *node);
bool		is_redir(t_token_type type);
bool		get_io_list(t_io_node **io_list);
t_node		*get_simple_cmd(void);
t_io_node	*new_io_node(t_token_type type, char *value);
void		append_io_node(t_io_node **io_list, t_io_node *new_node);
void		handle_parse_error(void);

#endif