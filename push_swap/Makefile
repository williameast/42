NAME = push_swap
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LIBFT_DIR = lib/libft
LIBFT = ./libft/libft.a
RM = rm -rf
SRCS = costs.c maths.c moves.c moves_extended.c position_calculator.c printing.c sanitize.c sort.c utilities.c reinsert.c
SRC = $(addprefix ./src/,$(SRCS))
OBJ_DIR = obj
OBJ = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

all: $(NAME)

$(LIBFT):
	@make -s -C $(LIBFT_DIR)

$(NAME): $(LIBFT) $(OBJ)
	@need_linking=false; \
	if [ ! -f $(NAME) ]; then \
		need_linking=true; \
	elif [ "$(OBJ)" -nt "$(NAME)" ]; then \
		need_linking=true; \
	elif [ "$(LIBFT)" -nt "$(NAME)" ]; then \
		need_linking=true; \
	fi; \
	if $$need_linking = true; then \
		echo "Linking executable $(NAME)..."; \
		$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -L./$(LIBFT_DIR) -lft; \
		echo "Executable $(NAME) update."; \
	else \
		echo "Nothing to do."; \
	fi

$(OBJ_DIR)/%.o: ./src/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

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
