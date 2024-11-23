NAME = push_swap
CC = cc
CFLAGS = -Wall -Wextra -Werror -Iinclude
LIBFT_DIR = lib/libft
LIBFT = $(LIBFT_DIR)/libft.a
SRC_DIR = src
OBJ_DIR = obj
SRCS = costs.c maths.c moves.c moves_extended.c position_calculator.c printing.c \
       sanitize.c sort.c utilities.c reinsert.c
SRCS := $(addprefix $(SRC_DIR)/, $(SRCS))
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))
RM = rm -rf

all: $(NAME)

$(LIBFT):
	@echo "Building libft..."
	@make -s -C $(LIBFT_DIR)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(LIBFT) $(OBJS)
	@echo "Linking $(NAME)..."
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -L$(LIBFT_DIR) -lft
	@echo "$(NAME) successfully built."

clean:
	@$(RM) $(OBJ_DIR)
	@make -s -C $(LIBFT_DIR) clean
	@echo "Cleaned build files."

fclean: clean
	@$(RM) $(NAME)
	@make -s -C $(LIBFT_DIR) fclean
	@echo "Full clean complete."

re: fclean all

.PHONY: all clean fclean re
