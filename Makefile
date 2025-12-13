NAME		= minishell
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g3 -fsanitize=address
INC			= -I includes -I libft
LIBS		= -lreadline
LIBFT_DIR	= libft
LIBFT		= $(LIBFT_DIR)/libft.a

SRCS		= src/main.c \
			  src/built-ins/ft_cd.c \
			  src/built-ins/ft_echo.c \
			  src/built-ins/ft_env.c \
			  src/built-ins/ft_exit.c \
			  src/built-ins/ft_export.c \
			  src/built-ins/ft_export_utils.c \
			  src/built-ins/ft_export_utils2.c \
			  src/built-ins/ft_export_utils3.c \
			  src/built-ins/ft_pwd.c \
			  src/built-ins/ft_unset.c \
			  src/env/init_env.c \
			  src/env/init_env_utils.c \
			  src/execution/exec_builtin.c \
			  src/execution/execute_multiple_commands.c \
			  src/execution/execution.c \
			  src/execution/execution_utils.c \
			  src/execution/execution_utils2.c \
			  src/execution/heredoc_utils.c \
			  src/execution/heredoc_utils2.c \
			  src/execution/pipes.c \
			  src/execution/set_path.c \
			  src/execution/set_path_utils.c \
			  src/execution/set_redirections.c \
			  src/execution/set_redirections_utils.c \
			  src/expanser/expander.c \
			  src/expanser/expander_utils.c \
			  src/expanser/field_split.c \
			  src/expanser/field_split_utils.c \
			  src/lexer/lexer.c \
			  src/lexer/lexer_utils.c \
			  src/lexer/tokenizer.c \
			  src/lexer/tokenizer_word.c \
			  src/parser/parser.c \
			  src/parser/parser_redir.c \
			  src/parser/parser_utils.c \
			  src/parser/parser_validator.c \
			  src/signals/set_signals.c \
			  src/utils/error.c \
			  src/utils/free_structs.c \
			  src/utils/init_structs.c \
			  src/utils/print_ast.c

OBJS		= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(INC) $(LIBS) $(LIBFT)
	@echo "Compiled successfully: $(NAME)"

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INC)

clean:
	rm -f $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@echo "Object files removed."

fclean: clean
	rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@echo "Executable files removed."

re: fclean all

.PHONY: all clean fclean re
