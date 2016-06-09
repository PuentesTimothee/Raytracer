/*
** initial.c for Obj in /home/aragon_m/modules/Infographie/gfx_raytracer2/BONUS/Obj
**
** Made by My-Lan Aragon
** Login   <aragon_m@epitech.net>
**
** Started on  Fri May  6 19:20:09 2016 My-Lan Aragon
** Last update Thu May 19 15:29:42 2016 My-Lan Aragon
*/

#include "raytracer1.h"

void	initial(t_fctn *tab_fct)
{
  tab_fct[0].s = "v";
  tab_fct[0].fct = &load_vertices;
  tab_fct[1].s = "f";
  tab_fct[1].fct = &load_faces;
}

int	initial_tri(t_triangle *tri)
{
  tri->nb_vertices = 0;
  tri->nb_vnorm = 0;
  tri->nb_face = 0;
  return (0);
}
