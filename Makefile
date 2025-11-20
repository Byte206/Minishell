# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gamorcil <gamorcil@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/15 12:14:21 by bmonterd          #+#    #+#              #
#    Updated: 2025/11/20 14:32:54 by gamorcil         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME		= minishell
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g
INC			= -I includes
LIBS		= -lreadline
LIBFT_DIR	= libft
LIBFT		= $(LIBFT_DIR)/libft.a

SRC_DIR		= src
SRC			= $(shell find $(SRC_DIR) -type f -name "*.c")
OBJ			= $(SRC:.c=.o)


all: $(NAME)

$(NAME): $(OBJ)
	@$(MAKE) -C $(LIBFT_DIR)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(INC) $(LIBS) $(LIBFT)
	@echo "Compiled successfully: $(NAME)"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)

clean:
	@rm -f $(OBJ)
	@echo "Object files removed."
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@rm -f $(NAME) $(NAME)_debug
	@echo "Executable files removed."
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all


# Compiles without warning flags (-Wall -Wextra -Werror)
# Keeps -g flag for debugging with gdb or lldb
debug:
	@echo "Compiling in DEBUG mode (no warning flags)..."
	@$(MAKE) -C $(LIBFT_DIR)
	@$(CC) -g $(SRC) -o $(NAME)_debug $(INC) $(LIBS) $(LIBFT)
	@echo "Debug executable created: ./$(NAME)_debug"


.PHONY: all clean fclean re debug
