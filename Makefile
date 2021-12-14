NAME	=	so_long
CC	=	clang
SRCS	=	./src/check_map.c \
			./src/error.c \
			./src/exit.c \
			./src/funçoes_aux.c \
			./src/key_hook.c \
			./src/check_moviment.c \
			./src/check_game.c \
			./src/read_map.c \
			./src/so_long.c \


OBJS	=	$(SRCS:%.c=%.o)
CFLAGS = -Wall -Wextra -Werror
FLAGS = -L ./libft -lft -L -lbsd -L ./minilibx-linux/ -lm  -lmlx -lXext -lX11

all: $(NAME)

$(NAME) : $(OBJS)
	make -C libft
	$(CC) $(OBJS) $(FLAGS) $(CFLAGS) -o $(NAME)

clean :
	rm -f $(OBJS)
	make clean -C libft

fclean : clean
	rm -f $(NAME)
	make fclean -C libft


re : fclean all

.PHONY:		all clean fclean re