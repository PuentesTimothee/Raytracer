/*
** my_math.c for  in /home/puente_t/rendu/Info/gfx_raytracer1
**
** Made by Timothée Puentes
** Login   <puente_t@epitech.net>
**
** Started on  Thu Feb 11 13:39:06 2016 Timothée Puentes
** Last update Thu May 19 14:16:27 2016 Timothée Puentes
*/

#include <lapin.h>
#include <math.h>
#include "raytracer1.h"

double			get_cos_a(t_3d_pos *vec1, t_3d_pos *vec2)
{
  double		lenght[2];
  double		c;

  lenght[0] = sqrt(vec1->x * vec1->x + vec1->y * vec1->y
		   + vec1->z * vec1->z);
  lenght[1] = sqrt(vec2->x * vec2->x + vec2->y * vec2->y
		   + vec2->z * vec2->z);
  c = vec2->x * vec1->x + vec2->y * vec1->y + vec2->z * vec1->z;
  c = c / (lenght[0] * lenght[1]);
  return (c);
}

t_3d_pos		get_normal_s(double alpha,
				     t_3d_pos *pos,
				     t_3d_pos *ray)
{
  t_3d_pos		norm;

  norm.x = -pos->x;
  norm.x += (ray[1].x + ray[0].x * alpha);
  norm.y = -pos->y;
  norm.y += (ray[1].y + ray[0].y * alpha);
  norm.z = -pos->z;
  norm.z += (ray[1].z + ray[0].z * alpha);
  return (norm);
}

t_3d_pos		*get_vector_normal(t_3d_pos *vec)
{
  double		lenght;

  lenght = sqrt(vec->x * vec->x + vec->y * vec->y + vec->z * vec->z);
  if (lenght == 0)
    return (vec);
  vec->x /= lenght;
  vec->y /= lenght;
  vec->z /= lenght;
  return (vec);
}

double		scalaire(t_3d_pos *vec1,
			 t_3d_pos *vec2,
			 double angle)
{
  double	res;

  res = sqrt(vec1->x * vec1->x + vec1->y * vec1->y + vec1->z * vec1->z);
  res *= sqrt(vec2->x * vec2->x + vec2->y * vec2->y + vec2->z * vec2->z);
  res *= cos(angle);
  return (res);
}

t_3d_pos	find_hit(double alpha, t_3d_pos *ray,
			 t_3d_pos *pos)
{
  t_3d_pos	new;

  new.x = (ray->x * alpha + pos->x);
  new.y = (ray->y * alpha + pos->y);
  new.z = (ray->z * alpha + pos->z);
  return (new);
}
