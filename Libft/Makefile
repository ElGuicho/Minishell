# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gmunoz <gmunoz@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/12 12:03:13 by gmunoz            #+#    #+#              #
#    Updated: 2025/07/14 21:01:39 by gmunoz           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := libft.a

CC := cc

CFLAGS := -Wall -Werror -Wextra

SRCS = ft_atoi.c ft_bzero.c ft_calloc.c ft_free_char.c ft_isalnum.c ft_isalpha.c \
	ft_isascii.c ft_isdigit.c ft_isprint.c ft_memchr.c ft_memcmp.c ft_memcpy.c \
	ft_memmove.c ft_memset.c ft_strchr.c ft_strdup.c ft_strjoin.c ft_strlcat.c \
	ft_strlen.c	ft_strlcpy.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c \
	ft_substr.c ft_tolower.c ft_toupper.c ft_split.c ft_itoa.c ft_strmapi.c \
	ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c

BNSSRCS = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c \
	ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
	ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c

OBJS := $(SRCS:.c=.o)

OBJS_BONUS := $(SRCS_BONUS:.c=.o)

INCLUDE_DIR := "../inc"

%.o: %.c
	@$(CC) -g $(CFLAGS) -c $< -I$(INCLUDE_DIR) -o $@

all: $(NAME) bonus

$(NAME): $(OBJS)
	@ar -rcs $@ $^

bonus: $(OBJS) $(OBJS_BONUS)
	@ar -rcs $(NAME) $^

clean:
	@rm -f $(OBJS) $(OBJS_BONUS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re