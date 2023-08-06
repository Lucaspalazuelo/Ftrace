##
## EPITECH PROJECT, 2023
## ftrace
## File description:
## Makefile
##

SRC	=	src/*.c

NAME	=	ftrace

all:
	gcc $(SRC) -lelf -g3 -o $(NAME)
	make clean

clean:
	rm -f *.o
	rm -f vgcore.*

fclean: clean
	rm -f $(NAME)

re:	fclean all
