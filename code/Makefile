NAME=pipex
CC=cc
CFLAGS=-Werror -Wextra -Wall
LIBFT=./libft/libft.a

SRC=	main.c \
		args.c \
		aux.c \

OBJ=$(SRC:.c=.o)

$(NAME): $(OBJ)
		@make all -C ./libft
		$(CC) $(OBJ) $(LIBFT) -o $(NAME)

all: $(NAME)

%.o: src/%.c
	$(CC) $(CFLAGS) -c $<

clean:
	@make clean -C ./libft
	@rm -f $(OBJ)

fclean: clean
	@make fclean -C ./libft
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re