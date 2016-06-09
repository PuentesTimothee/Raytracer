/*
** raytracing.c for  in /home/puente_t/rendu/Info/gfx_raytracer1
**
** Made by Timothée Puentes
** Login   <puente_t@epitech.net>
**
** Started on  Thu Feb  4 16:02:02 2016 Timothée Puentes
** Last update Sun May 22 23:15:28 2016 Timothée Puentes
*/

#include <lapin.h>
#include <math.h>
#include <stdio.h>
#include "raytracer1.h"

t_inter		init_inter()
{
  t_inter	inter;

  inter.alpha = -1;
  inter.mat.color.full = BLACK;
  inter.mat.color.argb[3] = 0;
  inter.mat.shine = -1;
  inter.mat.reflect = 0;
  inter.recur = 0;
  inter.normal.x = 0;
  inter.normal.y = 0;
  inter.normal.z = 0;
  return (inter);
}

static double	get_intensity(t_3d_pos *nray,
			      t_inter *inter,
			      t_sphere *light)
{
  t_3d_pos	hit;
  double	lenght;

  hit = find_hit(inter->alpha, nray, &nray[1]);
  hit = translate_vec3d(hit, light->pos);
  lenght = sqrt(hit.x * hit.x + hit.y * hit.y + hit.z * hit.z);
  lenght = (light->mat.shade - lenght);
  lenght = ((lenght < 0 && light->mat.shade != 0) ? (0) :
	    (lenght / light->mat.shade));
  return (lenght);
}

void		init_light(t_light *res)
{
  res->shadow = 0;
  res->specular.x = 0;
  res->specular.y = 0;
  res->specular.z = 0;
  res->diffuse = 0;
  res->totalintensity = 0;
}

void		compute_lights(t_data *data,
			       t_3d_pos *ray,
			       t_inter *inter)
{
  t_light	tmp;
  t_light	res;
  t_3d_pos	nray[2];

  init_light(&res);
  inter->rank = -1;
  while (++inter->rank < NBLIG)
    {
      nray[0] = ray[0];
      nray[1] = ray[1];
      res.intensity = get_intensity(nray, inter, &LIGHT[inter->rank]);
      tmp = compute_light(data, nray, inter);
      res.shadow += (tmp.shadow) / (double)(NBLIG);
      res.specular.x += tmp.specular.x * res.intensity;
      res.specular.y += tmp.specular.y * res.intensity;
      res.specular.z += tmp.specular.z * res.intensity;
      res.diffuse += (tmp.diffuse / (double)NBLIG);
      res.totalintensity += res.intensity / (double)NBLIG;
    }
  res.shadow = ((res.shadow < 0) ? (0) : (res.shadow));
  res.diffuse = ((8 * res.diffuse + 2 * 0.5) / 10.0) * res.totalintensity;
  compute_color(&inter->mat.color, &res);
}

void		ray_color(t_bunny_pixelarray *pix,
			  t_data *data,
			  t_3d_pos *ray,
			  t_bunny_position *pos)
{
  int		i;
  t_inter	inter;

  ray[0] = *get_vector_normal(&ray[0]);
  inter = init_inter();
  i = -1;
  while (++i < data->nb_obj)
    data->alpha[TYPE](&data->obj[i], ray, &inter);
  inter.recur = 0;
  if (inter.alpha > 0)
    {
      compute_lights(data, ray, &inter);
      if (inter.mat.color.argb[3] != 255)
	transparent_light(&inter.mat.color, data, ray, &inter);
      else if (inter.mat.reflect != 0)
	reflect_light(&inter.mat.color, data, ray, &inter);
    }
  tekpixel(pix, pos, &inter.mat.color);
}
