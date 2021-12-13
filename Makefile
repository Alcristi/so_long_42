NAME	=	so_long
CC	=	clang
SRCS	=	./src/check_map.c \
			./src/error.c \
			./src/exit.c \
			./src/funçoes_aux.c \
			./src/key_hook.c \
			./src/read_map.c \
			./src/so_long.c \
			./gnl/get_next_line.c \
			./gnl/get_next_line_utils.c

OBJS	=	$(SRCS:%.c=%.o)
CFLAGS = -Wall -Wextra -Werror
FLAGS = -L -lbsd -L ./minilibx-linux/ -lm  -lmlx -lXext -lX11

all: $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(OBJS) $(FLAGS) $(CFLAGS) -o $(NAME)

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY:		all clean fclean re