/*
** my.h for Obj in /home/aragon_m/modules/Infographie/gfx_raytracer2/BONUS/Obj
**
** Made by My-Lan Aragon
** Login   <aragon_m@epitech.net>
**
** Started on  Wed Apr 27 13:05:31 2016 My-Lan Aragon
** Last update Mon May  9 19:22:10 2016 Timothée Puentes
*/

#ifndef MY_H_
# define MY_H_

# include <stddef.h>
# define OPEN_F ("Open failed.\n")
# define MALLOC_F ("Malloc failed.\n")
# define W_NUM ("Bad number.\n")
# define W_VERTC ("Unknown vertices.\n")
# define W_NORM_FACE ("Face's numbers and norm's numbers are not equal.\n")

typedef struct	s_3d_pos
{
  double	x;
  double	y;
  double	z;
}		t_3d_pos;

typedef struct	s_face
{
  unsigned int 	f;
  unsigned int 	s;
  unsigned int	t;
}		t_face;

typedef struct	s_triangle
{
  unsigned int	nb_vertices;
  unsigned int	nb_vnorm;
  unsigned int	nb_face;
  t_3d_pos	*vertices;
  t_3d_pos	*vnorm;
  t_face	*face;
}		t_triangle;

typedef struct	s_fctn
{
  char		*s;
  int		(*fct)(t_triangle *tri, char **tab);
}		t_fctn;

/*
** basic.c
*/
int	my_strlen(char *str);
int	my_perror(char *str);
int	my_strcmp(char *s1, char *s2);
int	my_tablen(char **tab);
int	count_tri(t_triangle *tri);

/*
** load_obj.c
*/
int	load_obj(char *path);

/*
** my_str_to_wordtab.c
*/
char	**my_str_to_wordtab(char *str, char *delim);

/*
** initial.c
*/
void	initial(t_fctn *tab_fct);
int	initial_tri(t_triangle *tri);

/*
** my_getnbrdou.c
*/
double		my_getnbrdou(char *s);
unsigned int	my_getnbr(char *s);

/*
** load_faces.c
*/
int	load_vertices(t_triangle *tri, char **tab);
int	load_vnorm(t_triangle *tri, char **tab);
int	load_faces(t_triangle *tri, char **tab);

/*
** calc_vnorm.c
*/
int	calc_vnorm(t_triangle *tri);

/*
** my_memset.c
*/
void	*my_memset(void *s, int c, size_t n);

#endif /* !MY_H_ */
