# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cvalim-d <cvalim-d@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/19 11:12:38 by cvalim-d          #+#    #+#              #
#    Updated: 2024/11/19 14:10:23 by cvalim-d         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Name of the library
NAME		=	libftprintf.a

# Source files
SRC			=	ft_printf.c

# Object files
OBJS		=	$(SRC:%.c=%.o)

# Compiler and flags
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror

# Default target
all:		$(NAME)

# Build the library
$(NAME):		$(OBJS)
	ar rcs		$(NAME) $(OBJS)

# Clean object files
clean:
	rm -f		$(OBJS)

# Clean object files and the library
fclean:		clean
	rm -f		$(NAME)

# Rebuild the library
re:			fclean all

# Compiles .c files to .o files
%.o: %.c libftprintf.h
	$(CC)		$(CFLAGS) -c $< -o $@

.PHONY: all clean fclean re