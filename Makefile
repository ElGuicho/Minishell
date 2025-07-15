# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gmunoz <gmunoz@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/01 15:29:59 by gmunoz            #+#    #+#              #
#    Updated: 2025/07/15 23:31:10 by gmunoz           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		:= minishell

LIBFT		:= libft.a
LIBFT_PATH	:= "Libft"

CC			:= cc

CFLAGS		:= -Wall -Werror -Wextra

BUILTINS	:=	builtins/env.c \
				builtins/env_utils.c \
				builtins/cd.c \
				builtins/echo.c \
				builtins/exit.c \
				builtins/export.c \
				builtins/pwd.c \
				builtins/unset.c

CLEANING	:=	cleaning/clean_ms.c

EXEC		:=	exec/exec_utils.c \
				exec/init_tree.c \
				exec/exec.c \
				exec/exec_simple_cmd.c \
				exec/exec_redirect.c \
				exec/error_msg.c \
				exec/exist_check.c \
				exec/exec_builtin.c \
				exec/get_path.c

EXPANDER	:=	expander/expand.c \
				expander/expand_utils.c \
				expander/clean_empty_strs.c \
				expander/expander_split.c \
				expander/globber.c \
				expander/globber_utils.c \
				expander/asterisker.c \
				expander/strip_quotes.c \
				expander/heredoc_expander.c

PARSING		:=	parsing/parser.c \
				parsing/parser_utils.c \
				parsing/parser_utils2.c \
				parsing/parser_err.c \
				parsing/parser_nodes.c \
				parsing/parser_clear.c


TOKENIZING	:=	tokenizing/tokenizer.c \
				tokenizing/token_handler.c \
				tokenizing/tokenizer_list.c \
				tokenizing/tokenizer_utils.c \
				tokenizing/token_append.c

SRCS		:=	main.c signals.c \
				$(BUILTINS) \
				$(CLEANING) \
				$(EXEC) \
				$(EXPANDER) \
				$(PARSING) \
				$(TOKENIZING)
				

OBJS		:=	$(SRCS:.c=.o)

READLINE_PATH:=	/goinfre/homebrew/opt/readline

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -Iinclude -I$(READLINE_PATH)/include

all: $(NAME)

$(LIBFT):
	@make bonus -C $(LIBFT_PATH)

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) -o $(NAME) $(OBJS) -L$(LIBFT_PATH) -lft -L$(READLINE_PATH)/lib -lreadline

clean:
	@make clean -C $(LIBFT_PATH)
	@rm -f $(OBJS)

fclean: clean
	@make fclean -C $(LIBFT_PATH)
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re