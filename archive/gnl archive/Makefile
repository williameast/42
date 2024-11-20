# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ugerkens <ugerkens@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/14 16:05:56 by ugerkens          #+#    #+#              #
#    Updated: 2024/08/27 23:22:01 by William          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Variables
NAME			=	get_next_line.a
CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror -Isrc -Iinclude
RM				=	rm -rf

# Paths and Files
VPATH			=	src
SRCS			=	get_next_line.c get_next_line_utils.c
OBJS			=	$(addprefix build/,$(SRCS:.c=.o))

# Rules
$(NAME):		$(OBJS)
				ar rcs $(NAME) $(OBJS)

all:			$(NAME)

build:
				mkdir -p build

build/%.o:		%.c | build
				mkdir -p $(dir $@)
				$(CC) $(CFLAGS) -c $< -o $@

clean:
				$(RM) build

fclean:			clean
				$(RM) $(NAME)

re:				fclean all

.SILENT:

.PHONY:			all clean fclean rel
