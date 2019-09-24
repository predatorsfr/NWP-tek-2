##
## EPITECH PROJECT, 2017
## Makefile
## File description:
## Makefile
##

CC		=	gcc -o

RM		=	rm -f

CFLAGS	+=	-Wall -Wextra -Werror -I./include

SRCS	=	src/main.c			\
			src/add.c			\
			src/mem.c		\
			src/packet.c

NAME	=	myARPspoof

OBJS	=	$(SRCS:.c=.o)

COM		=	$(CC) $(NAME) $(OBJS) $(CFLAGS) $(INCLUDE)

all: 		$(NAME)

$(NAME): 	$(OBJS)
			$(COM)
clean:
			$(RM) $(OBJS)

fclean: 	clean
			$(RM) $(NAME)

re: 		fclean all

.PHONY: 	all clean fclean re
