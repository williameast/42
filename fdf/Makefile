#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: weast <weast@student.42berlin.de>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/20 12:50:41 by weast             #+#    #+#              #
#    Updated: 2025/01/20 12:50:41 by weast            ###   ########.fr        #
#                                                                              #
#******************************************************************************#
### COMPILATION ###
CC      = cc
FLAGS   = -Wall -Wextra -Werror -g

### DIRECTORIES ###
SRC_DIR     = src
OBJ_DIR     = obj
BIN_DIR     = bin
INC_DIR		= include

### LIBRARIES ###
LIBFT_DIR   = lib/libft
PRINTF_DIR  = lib/ft_printf
GNL_DIR     = lib/get_next_line
MLX_DIR     = lib/mlx

### LIBRARY TARGETS ###
LIBFT       = $(LIBFT_DIR)/libft.a
PRINTF      = $(PRINTF_DIR)/libftprintf.a
MLX         = $(MLX_DIR)/libmlx.a

### EXECUTABLE ###
NAME        = $(BIN_DIR)/fdf

### SOURCE FILES ###
SRC_FILES   = \
				utils.c \
				main.c \
				printing.c \
				map_mgmt.c \
				init.c \
				draw.c \
				affine.c \
				maffs.c \
				controls.c \
				cleanup.c \
				render.c \
				parsing.c \
				colours.c \

### HEADERS ###
HEADERS     =  \
				$(INC_DIR)/fdf.h \
				$(LIBFT_DIR)/libft.h \
				$(PRINTF_DIR)/ft_printf.h \
				$(GNL_DIR)/get_next_line.h

### OBJECT FILES ###
SRC_OBJS    = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))
GNL_OBJS    = $(addprefix $(OBJ_DIR)/, get_next_line.o get_next_line_utils.o)

### COLORS ###
NOC         = \033[0m
GREEN       = \033[1;32m
BLUE        = \033[1;34m
RED         = \033[1;31m

### RULES ###

all: $(NAME)

$(NAME): $(LIBFT) $(PRINTF) $(GNL_OBJS) $(SRC_OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(FLAGS) -L$(LIBFT_DIR) -L$(PRINTF_DIR) -L$(MLX_DIR) -o $@ $^ -g -lft -lftprintf -lmlx -lXext -lX11 -lm
	@echo "$(GREEN)Executable created: $(NAME)$(NOC)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(FLAGS) -Iinclude -I$(LIBFT_DIR) -I$(PRINTF_DIR) -I$(GNL_DIR) -I$(MLX_DIR) -c -o $@ $<
	@echo "$(BLUE)Compiled: $(notdir $<) -> $(notdir $@)$(NOC)"

$(OBJ_DIR)/get_next_line.o: $(GNL_DIR)/get_next_line.c $(HEADERS)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(FLAGS) -Iinclude -I$(LIBFT_DIR) -I$(PRINTF_DIR) -I$(GNL_DIR) -I$(MLX_DIR) -c -o $@ $<
	@echo "$(BLUE)Compiled: get_next_line.c -> get_next_line.o$(NOC)"

$(OBJ_DIR)/get_next_line_utils.o: $(GNL_DIR)/get_next_line_utils.c $(HEADERS)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(FLAGS) -Iinclude -I$(LIBFT_DIR) -I$(PRINTF_DIR) -I$(GNL_DIR) -I$(MLX_DIR) -c -o $@ $<
	@echo "$(BLUE)Compiled: get_next_line_utils.c -> get_next_line_utils.o$(NOC)"

$(LIBFT):
	@echo "$(GREEN)Building Libft$(NOC)"
	@make -C $(LIBFT_DIR)

$(PRINTF):
	@echo "$(GREEN)Building ft_printf$(NOC)"
	@make -C $(PRINTF_DIR)

$(MLX):
	@echo "$(GREEN)Building MLX$(NOC)"
	@make -C $(MLX_DIR)

clean:
	@echo "$(RED)Cleaning object files$(NOC)"
	@rm -rf $(OBJ_DIR)
	@make clean -C $(LIBFT_DIR)
	@make clean -C $(PRINTF_DIR)

fclean: clean
	@echo "$(RED)Removing executable and libraries$(NOC)"
	@rm -rf $(BIN_DIR)
	@make fclean -C $(LIBFT_DIR)
	@make fclean -C $(PRINTF_DIR)

get_deps:
	@echo "$(GREEN)installing dependencies $(NOC)"
	@sudo apt install libx11-dev libxext-dev libbsd-dev clang

install_mlx:
	@echo "$(BLUE)checking if MLX is installed$(NOC)"
	@echo ""

re: fclean all

.PHONY: all clean fclean re
