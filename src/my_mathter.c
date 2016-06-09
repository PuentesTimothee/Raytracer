/*
** my_mathter.c for  in /home/puente_t/rendu/Info/gfx_raytracer2
**
** Made by Timothée Puentes
** Login   <puente_t@epitech.net>
**
** Started on  Tue May 10 11:18:00 2016 Timothée Puentes
** Last update Thu May 12 17:23:46 2016 Timothée Puentes
*/

#include <math.h>
#include "raytracer1.h"

double		get_deg(t_3d_pos vec1, t_3d_pos vec2)
{
  return (acos(get_cos_a(&vec1, &vec2)));
}

double		dot(t_3d_pos vec1, t_3d_pos vec2)
{
  double	dot_prod;

  dot_prod = vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
  return (dot_prod);
}

t_3d_pos	cross(t_3d_pos vec1, t_3d_pos vec2)
{
  t_3d_pos	new;

  new.x = vec1.y * vec2.z - vec1.z * vec1.y;
  new.y = vec1.z * vec2.x - vec1.x * vec1.z;
  new.z = vec1.x * vec2.y - vec1.y * vec1.x;
  get_vector_normal(&new);
  return (new);
}
