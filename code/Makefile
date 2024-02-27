NAME=pipex
NAME_BONUS=pipex_bonus
CC=cc
CFLAGS=-Werror -Wextra -Wall
LIBFT=./libft/libft.a

SRC=	main.c \
		args.c \
		aux.c \

OBJ=$(SRC:.c=.o)

SRC_BONUS=	main_bonus.c \
			args_bonus.c \
			aux_bonus.c \
			here_doc_bonus.c

OBJ_BONUS=$(SRC_BONUS:.c=.o)

$(NAME): $(OBJ)
		@make all -C ./libft
		$(CC) $(OBJ) $(LIBFT) -o $(NAME)

$(NAME_BONUS): $(OBJ_BONUS)
		@make all -C ./libft
		$(CC) $(OBJ_BONUS) $(LIBFT) -o $(NAME_BONUS)

all: $(NAME)

bonus: $(NAME_BONUS)

%.o: src/%.c
	$(CC) $(CFLAGS) -c $<

clean:
	@make clean -C ./libft
	@rm -f $(OBJ) $(OBJ_BONUS)

fclean: clean
	@make fclean -C ./libft
	@rm -f $(NAME) $(NAME_BONUS)

re: fclean all

re_bonus: fclean bonus

.PHONY: all clean fclean re bonus re_bonus