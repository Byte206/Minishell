# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bmonterd <bmonterd@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/15 12:14:21 by bmonterd          #+#    #+#              #
#    Updated: 2025/11/01 15:36:46 by bmonterd         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME        = minishell
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g
INC         = -I includes -I libft
LIBS        = -lreadline -L libft -lft
SRC_DIR     = src
SRC         = $(shell find $(SRC_DIR) -type f -name "*.c")
OBJ         = $(SRC:.c=.o)

# Libft
LIBFT_DIR   = libft
LIBFT       = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(INC) $(LIBS)
	@echo "Compiled successfully: $(NAME)"

$(LIBFT):
	@make -C $(LIBFT_DIR)
	@echo "Libft compiled."

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)

clean:
	@make -C $(LIBFT_DIR) clean
	@rm -f $(OBJ)
	@echo "Object files removed."

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	@rm -f $(NAME) $(NAME)_debug
	@echo "Executable files removed."

re: fclean all

# Compiles without warning flags (-Wall -Wextra -Werror)
# Keeps -g flag for debugging with gdb or lldb
debug: $(LIBFT)
	@echo "Compiling in DEBUG mode (no warning flags)..."
	@$(CC) -g $(SRC) -o $(NAME)_debug $(INC) $(LIBS)
	@echo "Debug executable created: ./$(NAME)_debug"

.PHONY: all clean fclean re debug