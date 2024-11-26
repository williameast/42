#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: weast <weast@student.42berlin.de>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/26 14:25:08 by weast             #+#    #+#              #
#    Updated: 2024/11/26 15:06:12 by weast            ###   ########.fr        #
#                                                                              #
#******************************************************************************#
### COMPILATION ###
CC      = cc
FLAGS   = -Wall -Wextra -Werror

### EXE ###
NAME    = fdf

### INCLUDES ###
LIB_DIR = lib

LIBFT   = $(LIB_DIR)/libft
MLX     = $(LIB_DIR)/mlx
PRINTF	= $(LIB_DIR)/ft_printf
GNL		= $(LIB_DIR)/get_next_line/get_next_line.c


### PATHS ###
OBJ_PATH = obj
HEADER  = include
SRC_PATH = src

### SOURCE FILES ###
SOURCES = test.c

### OBJECTS ###
SRCS = $(addprefix $(SRC_PATH)/, $(SOURCES))
OBJS = $(addprefix $(OBJ_PATH)/, $(SOURCES:.c=.o))

### COLORS ###
NOC         = \033[0m
BOLD        = \033[1m
UNDERLINE   = \033[4m
BLACK       = \033[1;30m
RED         = \033[1;31m
GREEN       = \033[1;32m
YELLOW      = \033[1;33m
BLUE        = \033[1;34m
VIOLET      = \033[1;35m
CYAN        = \033[1;36m
WHITE       = \033[1;37m

### RULES ###

all: lib tmp $(NAME)

lib:
	@echo "$(GREEN)Creating lib files$(CYAN)"
	@make -C $(LIBFT)
	@make -C $(PRINTF)
	@make -C $(MLX)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(GNL) -L $(LIBFT) -L $(PRINTF) -L $(MLX) -o $@ $^ -lft -lmlx -lXext -lX11 -lm -lz
	@echo "$(GREEN)Project successfully compiled$(NOC)"

tmp:
	@mkdir -p $(OBJ_PATH)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c $(HEADER)/$(NAME).h
	@$(CC) $(FLAGS) -I$(HEADER) -I$(PRINTF) -I$(LIBFT) -I$(MLX) -c -o $@ $<
	@echo "$(BLUE)Creating object file -> $(WHITE)$(notdir $@)... $(RED)[Done]$(NOC)"

clean:
	@echo "$(GREEN)Cleaning library object files$(CYAN)"
	@make clean -C $(LIBFT)
	@make clean -C $(MLX)
	@make clean -C $(PRINTF)
	@rm -rf $(OBJ_PATH)

fclean: clean
	@echo "$(GREEN)Cleaning all files$(CYAN)"
	@rm -f $(NAME)
	@make fclean -C $(LIBFT)
	# @make fclean -C $(MLX)

re: fclean
	@$(MAKE) all -j

.PHONY: all lib tmp clean fclean re
