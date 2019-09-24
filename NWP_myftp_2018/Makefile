##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## Makefile.
##

CC	= gcc

RM	= rm -f


CFLAGS	+= -W -Wall -Wextra -Werror -g3
CFLAGS	+= -I./include

NAME	= myftp

SRCS	= ./main.c		\
		  ./src/str_to_wordtab.c	\
		  ./src/server/client.c		\
		  ./src/server/serv.c		\
		  ./src/command/cmd.c		\
		  ./src/command/run_c.c		\

OBJS	= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY:	all clean fclean re
