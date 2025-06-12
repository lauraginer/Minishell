# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lginer-m <lginer-m@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/09 20:49:03 by lginer-m          #+#    #+#              #
#    Updated: 2025/06/12 19:17:02 by lginer-m         ###   ########.fr        #
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
READLINE_INCLUDE = $(shell brew --prefix readline)/include
READLINE_LIB = $(shell brew --prefix readline)/lib
INCLUDES = -I./includes -I./lib/libft -I$(READLINE_INCLUDE)

# ============================================================================= #
#                                   SOURCES                                     #
# ============================================================================= #

SRCS_DIR := src/
PARSER_DIR := $(SRCS_DIR)src_parsing/
EXEC_DIR := $(SRCS_DIR)src_execute/

SRCS := \
	$(SRCS_DIR)main.c \

SRCS_PARSER := \

SRCS_EXEC := \
	
ALL_SRCS := $(SRCS) $(SRCS_PARSER) $(SRCS_EXEC)
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