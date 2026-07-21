NAME = codexion

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread -g

SRC = main.c parser.c utils.c init_hall.c dongles.c coders.c\
		routine.c init_dongle_and_coders.c run_coders.c heap.c \
		free_coders_and_dongles.c\

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c codexion.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re