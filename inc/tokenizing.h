/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmunoz <gmunoz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 20:42:37 by guido             #+#    #+#             */
/*   Updated: 2025/07/14 21:23:01 by gmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZING_H
# define TOKEN

# define PROMPT "minishell$ "

typedef enum e_token_type
{
	T_IDENTIFIER,
	T_LESS,
	T_GREAT,
	T_DLESS,
	T_DGREAT,
	T_PIPE,
	T_O_PARENT,
	T_C_PARENT,
	T_AND,
	T_OR,
	T_NL,
}	t_token_type;

typedef struct s_token
{
	t_token_type		type;
	char				*value;
	struct s_token		*next;
	struct s_token		*prev;
}	t_token;

t_token	*tokenize(void);
t_token	*token_handler(char *line);
void	clear_token_list(t_token **lst);
int		ft_isspace(char c);
void	skip_spaces(char **line);
t_token	*new_token(char *value, t_token_type type);
void	token_list_add_back(t_token **lst, t_token *new_token);
int		handle_separator(char **line, t_token **token_list);
int		append_separator(t_token_type type, char **line_ptr, t_token **token_list);
int		append_identifier(char **line_ptr, t_token **token_list);
void	print_quote_err(char quote);
bool	skip_quotes(char *line, size_t *i);
int		is_quote(char c);
int		is_separator(char *line);

#endif