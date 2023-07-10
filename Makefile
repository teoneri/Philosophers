GCC     = gcc
CFLAGS  = -g -Wall -Wextra -Werror -pthread -fsanitize=thread
FILES   = SRC/main.c SRC/lib_utils.c SRC/philo.c SRC/init.c SRC/philo_utils.c 
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