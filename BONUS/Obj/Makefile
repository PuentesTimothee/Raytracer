##
## Makefile for  in /home/puente_t/rendu/gfx_fdf1
## 
## Made by Timothée Puentes
## Login   <puente_t@epitech.net>
## 
## Started on  Thu Nov 12 16:07:04 2015 Timothée Puentes
## Last update Mon May  9 18:10:52 2016 Timothée Puentes
##

NAME		=	raytracer2

LIB		=	-L/home/${USER}/.froot/lib -llapin \
			-lsfml-audio -lsfml-graphics -lsfml-window \
			-lsfml-system -lstdc++ -ldl -lm

CC		=	cc -g3 -W -Wall -ansi -pedantic \
			-I/home/${USER}/.froot/include/ -Iinclude 

SRC		=	

OBJ		=	$(SRC:.c=.o)

all:		$(NAME)

$(NAME):	$(OBJ)
		gcc $(OBJ) $(LIB) -o $(NAME)

clean:
		rm -f $(OBJ)

fclean:		clean
		rm -f $(NAME)

re:		fclean all

.PHONY:		all clean fclean re
