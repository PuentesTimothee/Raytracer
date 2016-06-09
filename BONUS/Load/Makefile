##
## Makefile for  in /home/puente_t/rendu/gfx_fdf1
## 
## Made by Timothée Puentes
## Login   <puente_t@epitech.net>
## 
## Started on  Thu Nov 12 16:07:04 2015 Timothée Puentes
## Last update Wed Jan 20 11:14:12 2016 Timothée Puentes
##

NAME		=	load

LIB		=	-L/home/${USER}/.froot/lib -llapin \
			-lsfml-audio -lsfml-graphics -lsfml-window \
			-lsfml-system -lstdc++ -ldl -lm

CC		=	cc -W -Wall -Werror -ansi -pedantic \
			-I/home/${USER}/.froot/include/ -Iinclude 

SRC		=	main.c

OBJ		=	$(SRC:.c=.o)

all:		$(NAME)

$(NAME):	$(OBJ)
		gcc $(OBJ) $(LIB) -o $(NAME)

clean:
		rm -f $(OBJ)

fclean:		clean
		rm -f $(NAME)

re:		fclean all

