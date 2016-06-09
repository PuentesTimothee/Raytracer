##
## Makefile for  in /home/puente_t/rendu/gfx_fdf1
##
## Made by Timothée Puentes
## Login   <puente_t@epitech.net>
##
## Started on  Thu Nov 12 16:07:04 2015 Timothée Puentes
## Last update Thu May 26 16:49:55 2016 Timothée Puentes
##

NAME		=	raytracer2

LIB		=	-pthread \
			-L/home/${USER}/.froot/lib -llapin \
			-lsfml-audio -lsfml-graphics -lsfml-window \
			-lsfml-system -lstdc++ -ldl -lm

CC		=	cc -g -W -Wall -Werror -ansi \
			-I/home/${USER}/.froot/include/ -Iinc -ldl

RM		=	rm -f

ECHO            =       /bin/echo -e

GROUP		=	" By  aragon_m  puente_t  domage_j  rochel_s"

DEFAULT =       "\033[00m"
GREEN   =       "\033[0;32m"
TEAL    =       "\033[1;36m"
RED     =       "\033[0;31m"
PURP    =       "\033[0;35m"


SRC		=	src/main.c \
			src/pthread.c \
			src/useful_bis.c \
			src/save_bmp.c \
			src/init.c \
			src/my_atoi.c \
			src/useful.c \
			src/tekpixel.c \
			src/tekray.c \
			src/raytracing.c \
			src/my_math.c \
			src/my_mathbis.c \
			src/my_mathter.c \
			src/matrice.c \
			src/calc_cylinder.c \
			src/calc_sphere.c \
			src/calc_cone.c \
			src/calc_cube.c \
			src/calc_plan.c \
			src/extract.c \
			src/extractter.c \
			src/light.c \
			src/extractbis.c \
			src/reflected.c \
			src/aa_8x.c \
			src/error.c\
			src/texture_sphere.c \
			src/calc_triangle.c \
			src/bunny_dup.c\
			src/basic.c \
			src/load_obj.c \
			src/my_str_to_wordtab.c \
			src/load_faces.c \
			gnl/get_next_line.c \
			gnl/gnl_use.c \
			gnl/gnl2.c \
			src/initial.c \
			src/aa_supp.c \
			src/my_getnbrdou.c \
			src/calc_vnorm.c \
			src/my_memset.c \
			src/extract_plan.c\
			src/useful_load_cat.c

OBJ		=	$(SRC:.c=.o)

all:		$(NAME)

$(NAME):	$(OBJ)
		@gcc $(OBJ) $(LIB) -o $(NAME) && \
		$(ECHO) $(GREEN) "[OK]" $(TEAL) $(NAME) $(DEFAULT) || \
		$(ECHO) $(RED) "[FAILED]" $(TEAL) $(NAME)
	@$(ECHO) $(RED)
	@$(ECHO) "#######\                        ##\                                                             ######\ "
	@$(ECHO) "##  __##\                       ## |                                                           ##  __##\ "
	@$(ECHO) "## |  ## | ######\  ##\   ##\ #######\    #####\  ######\   ########\  #####\   ######\        \__/  ## |"
	@$(ECHO) "#######  | \____##\ ## |  ## |\_##  _|  ##  __##\ \____##\ ##  _____|##  __##\ ##  __##\        ######  |"
	@$(ECHO) "##  __##<  ####### |## |  ## |  ## |    ## |  \__|####### |## /      ######## |## |  \__|      ##  ____/ "
	@$(ECHO) "## |  ## |##  __## |## |  ## |  ## |##\ ## |     ##  __## |## |      ##   ____|## |            ## |"
	@$(ECHO) "## |  ## |\####### |\####### |  \####  |## |     \####### |\#######\ \#######\ ## |            ########\ "
	@$(ECHO) "\__|  \__| \_______| \____## |   \____/ \__|      \_______| \_______| \_______|\__|            \________|"
	@$(ECHO) "                    ##\   ## |"
	@$(ECHO) "                    \######  |"
	@$(ECHO) "                     \______/ "
	@$(ECHO) ''
	@$(ECHO) $(GROUP)
	@$(ECHO) ''
	@$(ECHO) $(DEFAULT)

clean:
		@$(RM) $(OBJ) && \
		$(ECHO) $(PURP) "[RM]" $(TEAL) "[OBJ]" $(DEFAULT)

fclean:		clean
		@$(RM) $(NAME) && \
		$(ECHO) $(PURP) "[RM]" $(TEAL) $(NAME) $(DEFAULT)

re:		fclean all

.c.o:
	@$(CC) $(LIB) -c $< -o $@ && \
	$(ECHO) $(GREEN) "[OK]" $(TEAL) $< $(DEFAULT) || \
	$(ECHO) $(RED) "[FAILED]" $(TEAL) $< $(NAME)

.PHONY: re all clean fclean .c.o
