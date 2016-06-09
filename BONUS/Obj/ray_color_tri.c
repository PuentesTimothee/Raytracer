/*
** ray_color_tri.c for Obj in /home/aragon_m/modules/Infographie/gfx_raytracer2/BONUS/Obj
**
** Made by My-Lan Aragon
** Login   <aragon_m@epitech.net>
**
** Started on  Mon May  9 16:30:14 2016 My-Lan Aragon
** Last update Mon May  9 19:21:14 2016 Timothée Puentes
*/

#include <lapin.h>
#include "raytracer1.h"

t_trian		get_t_trian(t_trian *trian, t_triangle obj, unsigned int i)
{
  trian->vec[0] = obj.vertices[obj.face[i].f - 1].x;
  trian->vec[1] = obj.vertices[obj.face[i].s - 1].y;
  trian->vec[2] = obj.vertices[obj.face[i].t - 1].z;
  trian->norm = obj.vnorm[i];
  return (trian);
}

void		ray_color_tri(t_bunny_pixelarray *pix,
			      t_data *data,
			      t_3d_pos *ray,
			      t_bunny_position *pos)
{
  unsigned int	i;
  t_trian	trian;
  t_inter	inter;

  inter = init_inter();
  i = -1;
  while (++i < data->tri.nb_face)
    {
      get_t_trian(&trian, data->tri, i);
      alpha_trian((t_obj *)trian, ray, &inter);
    }
  if (inter.alpha > 0)
    {
      if (inter.mat.reflect != 0)
	reflect_light(data, ray, &inter, 0);
      if (inter.mat.color.argb[3] != 255)
	transparent_light(data, ray, &inter);
      compute_lights(data, ray, &inter);
    }
  tekpixel(pix, pos, &inter.mat.color);
}
