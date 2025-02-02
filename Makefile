CC = cc

CFLAGS = -Wall -Wextra -Werror -g3

NAME = pipex

BONUS_NAME = pipex

SRC = pipex.c
BONUS = .bonus

UTILS = utils.c utils2.c printf.c utils1.c ft_split_cmd.c

OBJ = ${SRC:.c=.o} ${UTILS:.c=.o}

BONUS_SRC = pipex_bonus.c get_next_line_bonus.c  get_next_line_utils_bonus.c

BONUS_OBJ = ${BONUS_SRC:.c=.o} ${UTILS:.c=.o}

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) ${OBJ} -o ${NAME}

bonus: ${BONUS}

${BONUS}: ${BONUS_OBJ}
	@$(CC) $(CFLAGS) ${BONUS_OBJ} -o ${BONUS_NAME}
	@touch ${BONUS}

all : $(NAME)

clean:
	@rm -f $(OBJ) $(BONUS_OBJ) ${BONUS}

fclean: clean
	@rm -f $(NAME)

.PHONY: all clean fclean re bonus

re: fclean all
