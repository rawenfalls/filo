NAME =		philo

SRCS =		philo.c work_with_time.c
			
OBJS =		$(SRCS:.c=.o)

HEADER = 	philo.h

CC =		gcc

CFLAGS =	 -pthread #-Wall -Wextra -Werror -g3 -fsanitize=thread

%.o:		%.c $(HEADER)
			$(CC) $(CFLAGS) $(TEST) -c $< -o $(<:.c=.o)

all :		$(NAME)
			@echo "Make done"

$(NAME) :	$(OBJS)
			$(CC) $(CFLAGS) $(TEST) $(OBJS) -o $(NAME)

clean :
			@rm -f $(OBJS) $(HEADER).gch
			@echo "Make clean done"

fclean 	:	clean
			@rm -f $(NAME)
			@echo "Make fclean done"

re :		fclean all

norm:
			norminette *.c *.h

.PHONY :	all clean fclean re norm
