/*
** my_mathbis.c for  in /home/puente_t/rendu/Info/gfx_raytracer1
**
** Made by Timothée Puentes
** Login   <puente_t@epitech.net>
**
** Started on  Fri Feb 19 13:37:26 2016 Timothée Puentes
** Last update Sun May 22 23:04:56 2016 Timothée Puentes
*/

#include <lapin.h>
#include <math.h>
#include "raytracer1.h"

t_3d_pos	get_reflected(t_3d_pos *norm,
			      t_3d_pos *vec)
{
  t_3d_pos	reflected;
  double	scal;
  double	angle;

  angle = acos(get_cos_a(norm, vec));
  scal = scalaire(norm, vec, angle);
  reflected.x = -scal * 2 * norm->x + vec->x;
  reflected.y = -scal * 2 * norm->y + vec->y;
  reflected.z = -scal * 2 * norm->z + vec->z;
  return (reflected);
}

t_3d_pos	translate_vec3d(t_3d_pos vec,
				t_3d_pos to_move)
{
  t_3d_pos	new;

  new.x = vec.x - to_move.x;
  new.y = vec.y - to_move.y;
  new.z = vec.z - to_move.z;
  return (new);
}

void		vec_rev(t_3d_pos *vec)
{
  vec->x *= -1;
  vec->y *= -1;
  vec->z *= -1;
}

void		free_ray(t_data *data)
{
  bunny_delete_clipable(&data->pix->clipable);
  bunny_delete_clipable(&data->actual->clipable);
  bunny_free(data->light);
  bunny_free(data->obj);
  if (data->save != NULL)
    bunny_free(data->save);
  bunny_set_memory_check(true);
}
