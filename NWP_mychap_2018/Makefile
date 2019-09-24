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

NAME	= client

SRCS	= ./src/main.c		\
		  ./src/build.c		\
		  ./src/send.c		\
		  ./src/checksum.c	\

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
