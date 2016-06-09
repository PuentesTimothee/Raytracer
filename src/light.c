/*
** light.c for  in /home/puente_t/rendu/Info/gfx_raytracer1
**
** Made by Timothée Puentes
** Login   <puente_t@epitech.net>
**
** Started on  Thu Feb 18 16:09:23 2016 Timothée Puentes
** Last update Fri May 20 12:36:45 2016 Timothée Puentes
*/

#include <lapin.h>
#include <math.h>
#include <stdio.h>
#include "raytracer1.h"

t_3d_pos	specular_light(t_inter *inter,
			       t_3d_pos *ray,
			       t_3d_pos *lightray,
			       t_color *color)
{
  t_3d_pos	specular;
  double	x;
  t_3d_pos	reflected;

  reflected = get_reflected(&L_NORM, lightray);
  vec_rev(&reflected);
  x = -get_cos_a(&reflected, &ray[0]);
  if (x < 0)
    x = 0;
  x = pow(x, inter->mat.shine);
  specular.x = (x) * color->argb[0];
  specular.y = (x) * color->argb[1];
  specular.z = (x) * color->argb[2];
  return (specular);
}

int		check_light(t_3d_pos *lightpos,
			    t_3d_pos *ray,
			    double alpha)
{
  double       a_to_light;

  a_to_light = alpha;
  if (ray[0].x != 0)
    a_to_light = (lightpos->x - ray[1].x) / ray[0].x;
  else if (ray[0].y != 0)
    a_to_light = (lightpos->y - ray[1].y) / ray[0].y;
  else if (ray[0].z != 0)
    a_to_light = (lightpos->z - ray[1].z) / ray[0].z;
  if (alpha < a_to_light)
    return (1);
  return (0);
}

double		shadow_calc(t_3d_pos *ray,
			    t_data *data, t_inter *inter)
{
  int		i;
  t_inter	shadow;
  double	shade;
  int		c;

  shade = 0;
  c = 0;
  shadow = init_inter();
  while (check_light(&LIGHT[inter->rank].pos, ray, shadow.alpha)
	 && shadow.mat.color.argb[3] != 255)
    {
      shadow = init_inter();
      i = -1;
      while (++i < data->nb_obj)
	data->alpha[TYPE](&data->obj[i], ray, &shadow);
      if (shadow.alpha <= 0)
	break ;
      if (check_light(&LIGHT[inter->rank].pos, ray, shadow.alpha))
	shade += shadow.mat.color.argb[3] / 255.0;
      c += 1;
      ORI = find_hit(shadow.alpha + 0.1, &DIR, &ORI);
    }
  shade /= ((c == 0) ? (1) : (c));
  return (shade);
}

void		get_arroud_color(t_light *light,
				 double shade)
{
  light->specular.x += (1 - shade) * light->color.argb[0] / 15.0;
  light->specular.y += (1 - shade) * light->color.argb[1] / 15.0;
  light->specular.z += (1 - shade) * light->color.argb[2] / 15.0;
}

t_light		compute_light(t_data *data,
			      t_3d_pos *ray,
			      t_inter *inter)
{
  t_light	light;
  t_3d_pos	pos[2];

  pos[1] = find_hit(inter->alpha * 0.9, &ray[0], &ray[1]);
  pos[0] = translate_vec3d(LIGHT[inter->rank].pos, pos[1]);
  pos[0] = *get_vector_normal(&pos[0]);
  L_NORM = *get_vector_normal(&L_NORM);
  light.color = LIGHT[inter->rank].mat.color;
  light.diffuse = get_cos_a(&pos[0], &L_NORM);
  SPECULAR = specular_light(inter, ray, &pos[0],
			    &LIGHT[inter->rank].mat.color);
  light.shadow = shadow_calc(pos, data, inter);
  get_arroud_color(&light, ((light.shadow < 0) ? (0) : (light.shadow)));
  return (light);
}
