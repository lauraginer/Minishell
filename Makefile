# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lginer-m <lginer-m@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/09 20:49:03 by lginer-m          #+#    #+#              #
#    Updated: 2025/06/09 22:37:42 by lginer-m         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# ============================================================================= #
#                                  MINISHELL                                    #
# ============================================================================= #

NAME := minishell
CC := cc
CFLAGS := -g -Wall -Werror -Wextra \
		#-g -fsanitize=address,undefined \
		#-Wunreachable-code -Ofast \

LIBFT_DIR := Libft
LIBFT := $(LIBFT_DIR)/libft.a
INCLUDES := -I$(LIBFT_DIR) -Iinc -I/usr/include -I$(HOME)/.brew/include
LIBS := -lreadline

# ============================================================================= #
#                                   SOURCES                                     #
# ============================================================================= #

SRCS_DIR := src/
PARSER_DIR := $(SRCS_DIR)parser/
EXEC_DIR := $(SRCS_DIR)executor/

SRCS := \
	$(SRCS_DIR) \
	$(SRCS_DIR) \
	$(SRCS_DIR) \

SRCS_PARSER := \
	$(PARSER_DIR) \
	$(PARSER_DIR) \
	$(PARSER_DIR) \
	$(PARSER_DIR) \
	$(PARSER_DIR) \

SRCS_EXEC := \
	$(EXEC_DIR) \
	$(EXEC_DIR) \
	$(EXEC_DIR) \
	$(EXEC_DIR) \
	
ALL_SRCS := $(SRCS) $(SRCS_PARSER) $(SRCS_EXEC)
OBJS := $(ALL_SRCS:.c=.o)

# ============================================================================= #
#                                   COLORS                                      #
# ============================================================================= #

# Text Colors
BLACK       := \033[0;30m
RED         := \033[0;31m
GREEN       := \033[0;32m
YELLOW      := \033[0;33m
BLUE        := \033[0;34m
PURPLE      := \033[0;35m
CYAN        := \033[0;36m
WHITE       := \033[0;37m

# Background Colors
BG_BLACK    := \033[40m
BG_RED      := \033[41m
BG_GREEN    := \033[42m
BG_YELLOW   := \033[43m
BG_BLUE     := \033[44m
BG_PURPLE   := \033[45m
BG_CYAN     := \033[46m
BG_WHITE    := \033[47m

# Reset
RESET       := \033[0m

# ============================================================================= #
#                                    RULES                                      #
# ============================================================================= #

.PHONY: all clean fclean re bonus norminette test help

all: header $(NAME)
	@echo "$(GREEN)✅ Compilation completed successfully!$(RESET)"
	@echo "$(CYAN)🚀 Ready to use ./$(NAME)$(RESET)"

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
	@make -C $(LIBFT_DIR) clean --no-print-directory
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

test: $(NAME)
	@echo "$(CYAN)🧪 Running basic tests...$(RESET)"
	@echo "$(YELLOW)Testing echo...$(RESET)"
	@echo 'echo "Hello World!"' | ./$(NAME)
	@echo "$(YELLOW)Testing pwd...$(RESET)"
	@echo 'pwd' | ./$(NAME)

leak: $(NAME)
	@echo "$(RED)🔍 Running leak test...$(RESET)"
	@leaks --atExit -- ./$(NAME)

header:
	@clear
	@echo "$(CYAN)"
	@echo "╔══════════════════════════════════════════════════════════════════════════════╗"
	@echo "║                                                                              ║"
	@echo "║    ███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗            ║"
	@echo "║    ████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║            ║"
	@echo "║    ██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║            ║"
	@echo "║    ██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║            ║"
	@echo "║    ██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗       ║"
	@echo "║    ╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝       ║"
	@echo "║                                                                              ║"
	@echo "║$(YELLOW)                          ✨ 42 School Project ✨                             $(CYAN)║"
	@echo "║                                                                              ║"
	@echo "║$(GREEN)                            👥 jcaro-lo & lginer-m 👥                         $(CYAN)║"
	@echo "║                                                                              ║"
	@echo "╚══════════════════════════════════════════════════════════════════════════════╝"
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