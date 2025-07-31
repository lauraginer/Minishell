

# ============================================================================= #
#                                  MINISHELL                                    #
# ============================================================================= #

NAME := minishell
CC := cc
CFLAGS := -g -Wall -Werror -Wextra \
		#-g -fsanitize=address,undefined \
		#-Wunreachable-code -Ofast \

LIBFT_DIR := libft
LIBFT := $(LIBFT_DIR)/libft.a
INCLUDES := -I$(LIBFT_DIR) -Iinc -I/usr/include -I$(HOME)/.brew/include
LIBS := -lreadline

# ============================================================================= #
#                                   SOURCES                                     #
# ============================================================================= #

SRCS_DIR := src/
PARSER_DIR := $(SRCS_DIR)src_parse/
EXEC_DIR := $(SRCS_DIR)src_execute/
SIGNAL_DIR := $(SRCS_DIR)src_signal/

SRCS := \
	$(SRCS_DIR)main.c \

SRCS_PARSER := \
	$(addprefix $(PARSER_DIR), lexer.c \
	free_parse.c \
	token_list_utils.c \
	lexer_utils.c \
	expander.c \
	count_sub_tokens.c \
	split_sub_tokens.c \
	split_sub_tokens_utils.c \
	syntax_checker.c \
	transitions.c \
	ast.c \
	ast_utils.c )

BUILTINS_DIR := $(EXEC_DIR)built-ins/

SRCS_EXEC := \
	$(addprefix $(EXEC_DIR), execute_cmd.c \
	execute.c \
	utils_ex.c \
	redirections.c) \
	$(addprefix $(BUILTINS_DIR), echo.c \
	pwd.c \
	env.c \
	exit.c \
	export.c \
	unset.c \
	cd.c \
	built-ins.c \
	bs_utils.c)
	# test_env.c) # Comentado temporalmente - tiene su propio main

SRCS_SIGNALS := \
	$(addprefix $(SIGNAL_DIR), signals.c)

ALL_SRCS := $(SRCS) $(SRCS_PARSER) $(SRCS_EXEC) $(SRCS_SIGNALS)
OBJS := $(ALL_SRCS:.c=.o)

# ============================================================================= #
#                                   COLORS                                      #
# ============================================================================= #

BLACK       := \033[0;30m
RED         := \033[0;31m
GREEN       := \033[0;32m
YELLOW      := \033[0;33m
BLUE        := \033[0;34m
PURPLE      := \033[0;35m
CYAN        := \033[0;36m
WHITE       := \033[0;37m

RESET       := \033[0m

# ============================================================================= #
#                                    RULES                                      #
# ============================================================================= #

.PHONY: all clean fclean re bonus norminette test help cleanlib

all: header cleanlib $(NAME)
	@echo "$(GREEN)✅ Compilation completed successfully!$(RESET)"
	@echo "$(CYAN)🚀 Ready to use ./$(NAME)$(RESET)"

cleanlib:
	@echo "$(YELLOW)🧹 Cleaning library objects...$(RESET)"
	@make -C $(LIBFT_DIR) fclean --no-print-directory

$(NAME): $(LIBFT) $(OBJS)
	@echo "$(YELLOW)🔗 Linking $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LIBS) -o $(NAME)
	@echo "$(GREEN)✨ $(NAME) created successfully!$(RESET)"

%.o: %.c
	@echo "$(CYAN)⚙️  Compiling $<$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	@echo "$(PURPLE)📚 Building libft...$(RESET)"
	@make -C $(LIBFT_DIR) --no-print-directory
	@echo "$(GREEN)✅ Libft compiled!$(RESET)"

clean:
	@echo "$(YELLOW)🧹 Cleaning object files...$(RESET)"
	@rm -f $(OBJS)
	@find $(SRCS_DIR) -name "*.o" -type f -delete 2>/dev/null || true
	@make -C $(LIBFT_DIR) fclean --no-print-directory
	@echo "$(GREEN)✨ Object files cleaned!$(RESET)"

fclean: clean
	@echo "$(RED)🔥 Full clean...$(RESET)"
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean --no-print-directory
	@echo "$(GREEN)✨ Everything cleaned!$(RESET)"

re: fclean all

norminette:
	@echo "$(BLUE)📏 Running norminette...$(RESET)"
	@norminette $(ALL_SRCS) includes/ | grep -E "(Error|Warning)" || echo "$(GREEN)✅ Norminette: OK!$(RESET)"

header:
	@clear
	@echo "$(BLUE)"
	@echo "╔═══════════════════════════════════════════════════════════════════════════╗"
	@echo "║                                                                           ║"
	@echo "║    ███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗         ║"
	@echo "║    ████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║         ║"
	@echo "║    ██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║         ║"
	@echo "║    ██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║         ║"
	@echo "║    ██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗    ║"
	@echo "║    ╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝    ║"
	@echo "║                                                                           ║"
	@echo "║$(YELLOW)                         ✨ 42 School Project ✨                           $(BLUE)║"
	@echo "║                                                                           ║"
	@echo "║$(GREEN)                        👥 jcaro-lo & lginer-m 👥                          $(BLUE)║"
	@echo "║                                                                           ║"
	@echo "╚═══════════════════════════════════════════════════════════════════════════╝"
	@echo "$(RESET)"
	@echo "$(GREEN)🚀 Starting compilation...$(RESET)"

help:
	@echo "$(CYAN)📖 Minishell Makefile Help$(RESET)"
	@echo ""
	@echo "$(WHITE)Available targets:$(RESET)"
	@echo "  $(GREEN)all$(RESET)         - Compile the project"
	@echo "  $(YELLOW)clean$(RESET)       - Remove object files"
	@echo "  $(RED)fclean$(RESET)      - Remove all generated files"
	@echo "  $(PURPLE)re$(RESET)          - Clean and recompile"
	@echo "  $(BLUE)norminette$(RESET)  - Check code style"
	@echo "  $(CYAN)test$(RESET)        - Run basic tests"
	@echo "  $(RED)leak$(RESET)        - Run leak detection"
	@echo "  $(WHITE)help$(RESET)        - Show this help"
	@echo ""
	@echo "$(GREEN)💡 Example usage: make all$(RESET)"