#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: weast <weast@student.42berlin.de>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/20 14:00:21 by weast             #+#    #+#              #
#    Updated: 2025/01/29 15:51:23 by weast            ###   ########.fr        #
#                                                                              #
#******************************************************************************#

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

### LIBRARY TARGETS ###
LIBFT       = $(LIBFT_DIR)/libft.a
PRINTF      = $(PRINTF_DIR)/libftprintf.a

### EXECUTABLES ###
CLIENT      = $(BIN_DIR)/client
SERVER      = $(BIN_DIR)/server

### SOURCE FILES ###
CLIENT_SRC  = client.c client_utils.c
SERVER_SRC  = server.c server_utils.c

### OBJECT FILES ###
CLIENT_OBJS = $(addprefix $(OBJ_DIR)/, $(CLIENT_SRC:.c=.o))
SERVER_OBJS = $(addprefix $(OBJ_DIR)/, $(SERVER_SRC:.c=.o))

### HEADERS ###
HEADERS     =  \
				$(INC_DIR)/minitalk.h \
				$(LIBFT_DIR)/libft.h \
				$(PRINTF_DIR)/ft_printf.h \

### COLORS ###
NOC         = \033[0m
GREEN       = \033[1;32m
BLUE        = \033[1;34m
RED         = \033[1;31m

all: $(CLIENT) $(SERVER)

$(CLIENT): $(LIBFT) $(PRINTF) $(CLIENT_OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(FLAGS) -L$(LIBFT_DIR) -L$(PRINTF_DIR) -o $@ $^ -g -lft -lftprintf
	@echo "$(GREEN)Executable created: $(CLIENT)$(NOC)"

$(SERVER): $(LIBFT) $(PRINTF) $(SERVER_OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(FLAGS) -L$(LIBFT_DIR) -L$(PRINTF_DIR) -o $@ $^ -g -lft -lftprintf
	@echo "$(GREEN)Executable created: $(SERVER)$(NOC)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(FLAGS) -I$(INC_DIR) -I$(LIBFT_DIR) -I$(PRINTF_DIR) -c -o $@ $<
	@echo "$(BLUE)Compiled: $(notdir $<) -> $(notdir $@)$(NOC)"

$(LIBFT):
	@echo "$(GREEN)Building Libft$(NOC)"
	@make -C $(LIBFT_DIR)

$(PRINTF):
	@echo "$(GREEN)Building ft_printf$(NOC)"
	@make -C $(PRINTF_DIR)

clean:
	@echo "$(RED)Cleaning object files$(NOC)"
	@rm -rf $(OBJ_DIR)
	@make clean -C $(LIBFT_DIR)
	@make clean -C $(PRINTF_DIR)

fclean: clean
	@echo "$(RED)Removing executables and libraries$(NOC)"
	@rm -rf $(BIN_DIR)
	@make fclean -C $(LIBFT_DIR)
	@make fclean -C $(PRINTF_DIR)

re: fclean all

.PHONY: all clean fclean re run
