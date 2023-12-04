NAME	= philo
CC		= gcc
CFLAGS	= -Werror -Wall -Wextra -pthread

SRC_PATH = srcs/
OBJ_PATH = objects/

SRC		=	main.c \
			parsing.c \
			reaper.c \
			time.c \
			routine.c \
			init.c \
			output.c \
			exit.c

SRCS	= $(addprefix $(SRC_PATH), $(SRC))
OBJ		= $(SRC:.c=.o)
OBJS	= $(addprefix $(OBJ_PATH), $(OBJ))

INC		= -I ./include/

all: $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

clean:
	rm -rf $(OBJ_PATH)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all re clean fclean