GCC     = gcc
CFLAGS  = -g -Wall -Wextra -Werror -pthread
FILES   = SRC/main.c SRC/utils.c SRC/philo_actions.c
NAME    = philosophers
RM  = rm -f
OBJECTS=$(FILES:.c=.o)
BONUS_OBJ = $(SRC_BONUS:.c=.o)

all:    $(NAME)
$(NAME):    $(OBJECTS)
						$(GCC) $(CFLAGS) $(OBJECTS) -o $(NAME)
clean:
						@$(RM) $(OBJECTS)

fclean: clean
						@$(RM) $(NAME)

re:     fclean all
bonus:          all $(BONUS_OBJ)
						
.PHONY:     all clean fclean re