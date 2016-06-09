/*
** load_faces.c for Obj in /home/aragon_m/modules/Infographie/gfx_raytracer2/BONUS/Obj
**
** Made by My-Lan Aragon
** Login   <aragon_m@epitech.net>
**
** Started on  Mon May  2 12:24:23 2016 My-Lan Aragon
** Last update Tue May 17 15:19:35 2016 My-Lan Aragon
*/

#include <stdlib.h>
#include "raytracer1.h"
#include "lapin.h"

int		load_vertices(t_triangle *tri, char **tab)
{
  t_3d_pos	*tmp;
  unsigned int	i;

  i = 0;
  if ((tmp = bunny_malloc(sizeof(t_3d_pos) * (tri->nb_vertices + 1))) == NULL)
    return (my_perror(MALLOC_F));
  while (i != tri->nb_vertices)
    {
      tmp[i] = tri->vertices[i];
      i = i + 1;
    }
  if (((tmp[i].x = my_getnbrdou(tab[1])) == -1) ||
      ((tmp[i].y = my_getnbrdou(tab[2])) == -1) ||
      ((tmp[i].z = my_getnbrdou(tab[3])) == -1))
    return (-1);
  tri->vertices = tmp;
  tri->nb_vertices += 1;
  return (0);
}

int		load_vnorm(t_triangle *tri, char **tab)
{
  t_3d_pos	*tmp;
  unsigned int	i;

  i = 0;
  if ((tmp = bunny_malloc(sizeof(t_3d_pos) * (tri->nb_vnorm + 1))) == NULL)
    return (my_perror(MALLOC_F));
  while (i != tri->nb_vnorm)
    {
      tmp[i] = tri->vnorm[i];
      i = i + 1;
    }
  if (((tmp[i].x = my_getnbrdou(tab[1])) == -1) ||
      ((tmp[i].y = my_getnbrdou(tab[2])) == -1) ||
      ((tmp[i].z = my_getnbrdou(tab[3])) == -1))
    return (-1);
  tri->vnorm = tmp;
  tri->nb_vnorm += 1;
  return (0);
}

int		load_second_face(t_triangle *tri, char **tab)
{
  t_face	*tmp;
  unsigned int	i;

  i = 0;
  if ((tmp = bunny_malloc(sizeof(t_face) * (tri->nb_face + 1))) == NULL)
    return (my_perror(MALLOC_F));
  while (i != tri->nb_face)
    {
      tmp[i] = tri->face[i];
      i = i + 1;
    }
  if (((tmp[i].f = my_getnbr(tab[1])) == 0) ||
      ((tmp[i].s = my_getnbr(tab[4])) == 0) ||
      ((tmp[i].t = my_getnbr(tab[3])) == 0))
    return (-1);
  if (tmp[i].f > tri->nb_vertices ||
      tmp[i].s > tri->nb_vertices ||
      tmp[i].t > tri->nb_vertices)
    return (my_perror(W_VERTC));
  tri->face = tmp;
  tri->nb_face += 1;
  return (0);
}

int		load_faces(t_triangle *tri, char **tab)
{
  t_face	*tmp;
  unsigned int	i;

  i = 0;
  if ((tmp = bunny_malloc(sizeof(t_face) * (tri->nb_face + 1))) == NULL)
    return (my_perror(MALLOC_F));
  while (i != tri->nb_face)
    {
      tmp[i] = tri->face[i];
      i = i + 1;
    }
  if (((tmp[i].f = my_getnbr(tab[1])) == 0) ||
      ((tmp[i].s = my_getnbr(tab[2])) == 0) ||
      ((tmp[i].t = my_getnbr(tab[3])) == 0))
    return (-1);
  if (tmp[i].f > tri->nb_vertices ||
      tmp[i].s > tri->nb_vertices ||
      tmp[i].t > tri->nb_vertices)
    return (my_perror(W_VERTC));
  tri->face = tmp;
  tri->nb_face += 1;
  if (my_tablen(tab) == 5)
    if (load_second_face(tri, tab) == -1)
      return (-1);
  return (0);
}
