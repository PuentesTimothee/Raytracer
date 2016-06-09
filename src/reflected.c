/*
** reflected.c for  in /home/puente_t/rendu/Info/gfx_raytracer1
**
** Made by Timothée Puentes
** Login   <puente_t@epitech.net>
**
** Started on  Fri Feb 26 12:07:35 2016 Timothée Puentes
** Last update Fri May 20 13:53:15 2016 Timothée Puentes
*/

#include <lapin.h>
#include "raytracer1.h"

static void	reflect_color(t_color *color,
			      t_color *ncolor,
			      t_inter *inter)
{
  int		new[3];

  new[0] = (REFLET(0) + OLD_REFLEC(0));
  new[1] = (REFLET(1) + OLD_REFLEC(1));
  new[2] = (REFLET(2) + OLD_REFLEC(2));
  color->argb[0] = ((new[0] > 255) ? (255) : (new[0]));
  color->argb[1] = ((new[1] > 255) ? (255) : (new[1]));
  color->argb[2] = ((new[2] > 255) ? (255) : (new[2]));
}

void		reflect_light(t_color *color,
			      t_data *data,
			      t_3d_pos *ray,
			      t_inter *inter)
{
  int		i;
  t_inter	ninter;
  t_3d_pos	reflec[2];

  if (++inter->recur > 15)
    return ;
  reflec[0] = get_reflected(&L_NORM, ray);
  reflec[1] = find_hit(inter->alpha * 0.9, ray, &ray[1]);
  ninter = init_inter();
  ninter.recur = inter->recur;
  i = -1;
  while (++i < data->nb_obj)
    data->alpha[TYPE](&data->obj[i], reflec, &ninter);
  if (ninter.mat.color.argb[3] != 255)
    transparent_light(color, data, &reflec[0], inter);
  else if (ninter.mat.reflect != 0)
    reflect_light(color, data, &reflec[0], inter);
  compute_lights(data, reflec, &ninter);
  reflect_color(color, &ninter.mat.color, inter);
  if (ninter.alpha <= 0)
    return ;
}

static void	transpar_color(t_color *color,
			       t_color *ncolor)
{
  double	perc;
  int		new[3];

  perc = color->argb[3] / 255.0;
  new[0] = color->argb[0] * perc + ncolor->argb[0] * (1 - perc);
  new[1] = color->argb[1] * perc + ncolor->argb[1] * (1 - perc);
  new[2] = color->argb[2] * perc + ncolor->argb[2] * (1 - perc);
  color->argb[0] = ((new[0] > 255) ? (255) : (new[0]));
  color->argb[1] = ((new[1] > 255) ? (255) : (new[1]));
  color->argb[2] = ((new[2] > 255) ? (255) : (new[2]));
  color->argb[3] = ncolor->argb[3];
}

t_3d_pos	get_diffraction(t_3d_pos *ori,
				t_3d_pos *norm)
{
  t_3d_pos	new;

  new.x = ori->x * 0.8 + norm->x * (1 - 0.8);
  new.y = ori->y * 0.8 + norm->y * (1 - 0.8);
  new.z = ori->z * 0.8 + norm->z * (1 - 0.8);
  return (new);
}

void		transparent_light(t_color *color,
				  t_data *data,
				  t_3d_pos *ray,
				  t_inter *inter)
{
  int		i;
  t_inter	ninter;
  t_3d_pos	transpar[2];

  if (++inter->recur > 15)
    return ;
  transpar[0] = get_diffraction(&ray[0], &inter->normal);
  transpar[1] = find_hit(inter->alpha + 0.5, ray, &ray[1]);
  ninter = init_inter();
  i = -1;
  while (++i < data->nb_obj)
    data->alpha[TYPE](&data->obj[i], transpar, &ninter);
  ninter.recur = inter->recur;
  if (ninter.alpha <= 0)
    return ;
  inter->normal = ninter.normal;
  if (ninter.mat.color.argb[3] != 255)
    transparent_light(color, data, &transpar[0], inter);
  else if (ninter.mat.reflect != 0)
    reflect_light(color, data, &transpar[0], inter);
  compute_lights(data, transpar, &ninter);
  transpar_color(color, &ninter.mat.color);
}
