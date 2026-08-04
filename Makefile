NAME = codexion

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread -g

SRC_DIR = src
INC_DIR = inc
OBJ_DIR = obj

SRC = main.c parser.c utils.c init_hall.c dongles.c coders.c compiling.c\
		routine.c init_dongle_and_coders.c run_coders.c heap.c\
		acquering_dongles.c print_error.c monitor_burnout.c

OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
INC = $(INC_DIR)/codexion.h

CFLAGS += -I$(INC_DIR)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
	rm -rf $(OBJ_DIR)

re: fclean all

.PHONY: all clean fclean re
