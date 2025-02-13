# ======================== #
#         COLORS           #
# ======================== #
RESET   = \033[0m
RED     = \033[1;31m
GREEN   = \033[1;32m
YELLOW  = \033[1;33m
BLUE    = \033[1;34m
MAGENTA = \033[1;35m
CYAN    = \033[1;36m
WHITE   = \033[1;37m

# ======================== #
#       FLAGS              #
# ======================== #
CC        = cc
FLAGS     = -Wall -Werror -Wextra
READLINE  = -lreadline #-L/opt/homebrew/opt/readline

NAME      = minishell

# ======================== #
#       PATHS              #
# ======================== #
LIBFT_DIR    = ./Library
SRC_DIR      = ./src
OBJ_DIR      = $(SRC_DIR)/obj

# ======================== #
#        SRC/OBJ           #
# ======================== #
LIBFT     = $(LIBFT_DIR)/libft.a

SRC_FILES = main.c \
	    $(addprefix utils/, general_functions.c list_struct_functions.c token_struct_functions.c free_structs.c) \
	    $(addprefix parsing/, parsing.c build_tokens.c parse_syntax.c convert_quotes.c expand_vars.c define_tokens.c build_tree.c find_var_value.c parsing_utils.c error_handling.c ) \
	    $(addprefix builtins/, exit.c  pwd.c echo.c cd.c init_builtins.c  new_env.c new_export_variables.c new_unset.c new_export.c manager_export.c manager_unset.c) \
	    $(addprefix executer/, prepare_path.c redirections.c signals.c)

SRC  = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

# ======================== #
#        RULES             #
# ======================== #
all: $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(addprefix $(OBJ_DIR)/, builtins utils executer parsing)
	@echo "$(YELLOW)Created object directory: $(OBJ_DIR)$(RESET)"

$(LIBFT):
	@echo "$(CYAN)Compiling Libft...$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@echo "$(MAGENTA)Compiling: $<$(RESET)"
	@$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(FLAGS) $(OBJS) $(LIBFT) $(READLINE) -o $(NAME)
	@echo "$(GREEN)Compilation successful! ✅$(RESET)"
	@echo "$(BLUE)Running checks...$(RESET)"
	@if [ -f $(NAME) ]; then echo "$(GREEN)$(NAME) created successfully! 🎉$(RESET)"; fi

valgrind: $(NAME)
	@echo "$(YELLOW)Running with Valgrind... 🧠$(RESET)"
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=readline.supp ./$(NAME)

clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	@rm -rf $(OBJ_DIR)
	@echo "$(GREEN)Object files cleaned!$(RESET)"

fclean: clean
	@echo "$(RED)Removing executable...$(RESET)"
	@rm -f $(NAME)
	@echo "$(GREEN)Executable removed!$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

# ======================== #
#        PHONY             #
# ======================== #
.PHONY: all clean fclean re valgrind
