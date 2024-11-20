NAME = libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs
RM = rm -f

FILES =	ft_atoi ft_bzero ft_calloc ft_isalpha ft_isalnum \
		ft_isascii ft_isdigit ft_isprint ft_memchr ft_memcmp \
		ft_memcpy ft_memmove ft_memset ft_strchr ft_strdup \
		ft_strlcat ft_strlcpy ft_strlen ft_strncmp ft_strnstr \
		ft_strrchr ft_tolower ft_toupper ft_substr ft_strjoin \
		ft_strtrim ft_split ft_itoa ft_strmapi ft_striteri \
		ft_putchar_fd ft_putstr_fd ft_putendl_fd ft_putnbr_fd


# FILES_B = 	ft_lstnew ft_lstadd_front ft_lstsize

SRCS_DIR = ./
SRCS = $(addprefix $(SRCS_DIR), $(addsuffix .c, $(FILES)))
SRCS_B = $(addprefix $(SRCS_DIR), $(addsuffix .c, $(FILES_B)))

OBJS_DIR = ./
OBJS = $(addprefix $(OBJS_DIR), $(addsuffix .o, $(FILES)))
OBJS_B = $(addprefix $(OBJS_DIR), $(addsuffix .o, $(FILES_B)))

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJS)
	$(AR) $@ $^

# bonus: $(OBJS) $(OBJS_B)
# 	$(AR) $(NAME) $^

all: $(NAME)

clean:
	$(RM) $(OBJS) $(OBJS_B)

fclean: clean
	$(RM) $(NAME)

re: fclean all

so:
	$(CC) -nostartfiles -fPIC $(CFLAGS) $(SRCS)
	$(CC) -nostartfiles -shared -o libft.so $(OBJS)

.PHONY: all clean fclean re
