NAME = lc3Sim

CC = gcc 

SRCS = srcs/main.c srcs/ops.c srcs/traps.c \
	srcs/utils.c srcs/loadPrograms.c

OBJS = ${SRCS:.c=.o}

RM = rm -f

all: $(NAME)

$(NAME):	$(OBJS)
		$(CC) $(OBJS) -o $(NAME)

clean:
		$(RM) $(OBJS)

fclean: clean
		$(RM) $(NAME)

re: fclean

.PHONY: all clean fclean re