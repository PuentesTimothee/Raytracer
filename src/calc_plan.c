/*
** calc_plan.c for  in /home/puente_t/rendu/Info/gfx_raytracer1/src
**
** Made by Timothée Puentes
** Login   <puente_t@epitech.net>
**
** Started on  Thu Feb 18 12:55:27 2016 Timothée Puentes
** Last update Thu May 12 15:28:15 2016 Timothée Puentes
*/

#include <lapin.h>
#include <stdio.h>
#include "raytracer1.h"

int			my_abs(double nb)
{
  if (nb >= 0)
    return (nb);
  nb *= -1;
  nb += 1;
  return (nb);
}

t_color			getpixel(const t_bunny_pixelarray *pix,
				 const t_3d_pos *pos)
{
  unsigned int		*buff;
  int			c;
  t_bunny_position	p;
  t_color		color;

  color.full = 0;
  p.x = (int)(my_abs(pos->x)) % pix->clipable.clip_width;
  p.y = (int)(my_abs(pos->z)) % pix->clipable.clip_height;
  c = p.x + (pix->clipable.clip_width * p.y);
  buff = pix->pixels;
  if (p.y <= pix->clipable.clip_height && p.y >= 0
      && p.x >= 0 && p.x <= pix->clipable.clip_width)
    color.full = buff[c];
  return (color);
}

void			alpha_plan(t_obj *obj, t_3d_pos *ray,
				   t_inter *inter)
{
  t_3d_pos	nray[2];
  t_3d_pos	hit;
  double	alpha;
  t_mat		mat;

  nray[0] = three_matrice(&ray[0], &obj->plan.rot);
  if (nray[0].y == 0)
    return ;
  nray[1] = three_matrice(&ray[1], &obj->plan.rot);
  alpha = (obj->plan.norm + obj->plan.pos.y - nray[1].y) / nray[0].y;
  hit.x = nray[1].x + nray[0].x * alpha + obj->plan.pos.x;
  hit.z = nray[1].z + nray[0].z * alpha + obj->plan.pos.z;
  mat = obj->plan.mat;
  if (obj->plan.texture != NULL)
    mat.color = getpixel(obj->plan.texture, &hit);
  else
    {
      if (my_abs(hit.x) % 2 == 1 && my_abs(hit.z) % 2 == 0)
	mat.color = obj->plan.mat.color_bis;
      if (my_abs(hit.x) % 2 == 0 && my_abs(hit.z) % 2 == 1)
	mat.color = obj->plan.mat.color_bis;
    }
  if (alpha > MIN && (alpha < inter->alpha || inter->alpha < MIN))
    *inter = set_inter(alpha, mat, NORMAL_PCAP);
}
