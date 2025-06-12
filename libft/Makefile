# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jcaro-lo <jcaro-lo@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/11 20:40:10 by jcaro-lo          #+#    #+#              #
#    Updated: 2025/04/19 10:57:53 by jcaro-lo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_strlen.c ft_memset.c\
	ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c\
	ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c\
	ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c\
	ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c

#LIBFT BONUS

SRC += ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c\
 	ft_lstadd_back_bonus.c ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c

#GET NEXT LINE FILES

SRC += get_next_line_bonus.c get_next_line_utils_bonus.c

#PRINTF FILES

SRC += ft_print_char.c ft_print_hexa_lower.c ft_print_hexa_upper.c ft_print_int.c\
	ft_print_ptr.c ft_print_string.c ft_print_unsigint.c ft_printf.c

#NEW ADDITIONS

SRC += ft_is_space.c ft_del_pointer.c ft_lstreverse.c ft_abs.c

OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME):$(OBJS)
	@ar rcs $(NAME) $(OBJS)

%.o: %.c
	@$(CC) -c $(CFLAGS)  $< -o $@

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re 