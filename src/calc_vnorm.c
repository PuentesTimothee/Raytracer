/*
** calc_vnorm.c for Obj in /home/aragon_m/modules/Infographie/gfx_raytracer2/BONUS/Obj
**
** Made by My-Lan Aragon
** Login   <aragon_m@epitech.net>
**
** Started on  Sat May  7 22:39:49 2016 My-Lan Aragon
** Last update Mon May  9 19:45:16 2016 Timothée Puentes
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "lapin.h"
#include "raytracer1.h"

static t_3d_pos	norm_vec(t_3d_pos vec)
{
  double	norm;

  norm = sqrt(pow(vec.x, 2) + pow(vec.y, 2) + pow(vec.z, 2));
  vec.x = vec.x / norm;
  vec.y = vec.y / norm;
  vec.z = vec.z / norm;
  return (vec);
}

static t_3d_pos	calc_norm(t_face face, t_3d_pos *vertices)
{
  t_3d_pos	norm;

  norm.x = ((vertices[face.s - 1].y - vertices[face.f - 1].y) *
	    (vertices[face.t - 1].z - vertices[face.f - 1].z)) -
    ((vertices[face.s - 1].z - vertices[face.f - 1].z) *
     (vertices[face.t - 1].y - vertices[face.f - 1].y));
  norm.y = ((vertices[face.s - 1].z - vertices[face.f - 1].z) *
	    (vertices[face.t - 1].x - vertices[face.f - 1].x)) -
    ((vertices[face.s - 1].x - vertices[face.f - 1].x) *
     (vertices[face.t - 1].z - vertices[face.f - 1].z));
  norm.z = ((vertices[face.s - 1].x - vertices[face.f - 1].x) *
	    (vertices[face.t - 1].y - vertices[face.f - 1].y)) -
    ((vertices[face.s - 1].y - vertices[face.f - 1].y) *
     (vertices[face.t - 1].x - vertices[face.f - 1].x));
  norm = norm_vec(norm);
  return (norm);
}

int		calc_vnorm(t_triangle *tri)
{
  if ((tri->vnorm = bunny_malloc(sizeof(t_3d_pos) * tri->nb_face)) == NULL)
    return (my_perror(MALLOC_F));
  while (tri->nb_vnorm != tri->nb_face)
    {
      tri->vnorm[tri->nb_vnorm]
	= calc_norm(tri->face[tri->nb_vnorm], tri->vertices);
      tri->nb_vnorm = tri->nb_vnorm + 1;
    }
  return (0);
}
