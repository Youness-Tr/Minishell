CC = cc
CFLAGS = -Wall -Wextra -Werror

NAME = minishell

LIBFT_DIR = Libft
LIBFT = $(LIBFT_DIR)/libft.a

SRC = Main/main.c Main/mtools.c
SRC += Expand/expander.c Expand/exputils.c Expand/exp_heredoc.c Expand/exp_tool.c
SRC += Builtins/env.c Builtins/exit.c Builtins/echo.c Builtins/export.c Builtins/exit_tools.c
SRC += Builtins/pwd.c Builtins/unset.c Builtins/get_set.c Builtins/cd.c
SRC += Builtins/export_utils.c Builtins/export_helper.c Builtins/env_utils.c
SRC += Lexer/lexical.c Lexer/lextools.c Lexer/token.c Lexer/lex_utils.c Lexer/token_tools.c
SRC += Leaks/free_all.c Leaks/garbedge.c
SRC += Parser/ft_parser.c Parser/putils.c Parser/tools.c Parser/left_hand.c
SRC += Executer/ft_execute.c Executer/ex_utils.c Executer/ex_heredoc.c Executer/ex_io.c
SRC += Executer/ex_builtins.c Executer/ex_pipes.c Executer/ex_error.c
SRC += Executer/ex_io_tools.c Executer/ex_tools.c  Executer/ex_cmd.c Executer/ex_pipeline.c
SRC += Executer/ex_and.c Executer/ex_or.c Executer/ex_args.c
SRC += signals/signal.c wildcard/asterisk.c wildcard/astirisk_tool.c

OBJ = $(SRC:.c=.o)

all: $(LIBFT) $(NAME)

$(LIBFT):
	@echo "Building Libft..."
	@$(MAKE) -C $(LIBFT_DIR)
	@$(MAKE) -C $(LIBFT_DIR) bonus

$(NAME): $(LIBFT) $(OBJ)
	@echo "Linking $(NAME)..."
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -lreadline -L$(LIBFT_DIR) -lft
	@sleep 1
	@echo "Creating minishell is Done!"

clean:
	@echo "Cleaning object files.."
	@rm -rf $(OBJ)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@echo "Removing ..."
	@rm -rf $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@sleep 1
	@echo "Removing minishell is Done!"

re: fclean all

.PHONY: all clean fclean re
