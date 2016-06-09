/*
** texture_sphere.c for RT2 in /home/domage_j/rendu/TODO/gfx_raytracer2/src
**
** Made by domage jean-adrien
** Login   <domage_j@epitech.net>
**
** Started on  Tue Apr 19 17:56:51 2016 domage jean-adrien
** Last update Sun May 22 11:48:51 2016 Jean-Adrien Domage
*/

#include <lapin.h>
#include <math.h>
#include "raytracer1.h"

unsigned int		get_texture_color(t_bunny_pixelarray *pix,
					  int x,
					  int y)
{
  t_color		color;

  if (x < 0)
    x = x * -1;
  if (y < 0)
    y = y * -1;
  if (x > pix->clipable.clip_width)
    x = x % pix->clipable.clip_width;
  if (y > pix->clipable.clip_height)
    y = y % pix->clipable.clip_height;
  color.full = ((unsigned int *) pix->pixels)
    [(pix->clipable.clip_width * y) + x];
  return (color.full);
}

void		sphere_texturing(t_obj *obj, t_3d_pos *ray,
				 double alpha, t_mat *mat)
{
  double	x;
  double	y;
  int		height;
  int		width;
  t_3d_pos	hit;

  x = alpha;
  if (obj->sphe.texture != NULL)
    {
      hit = find_hit(alpha, &ray[0], &ray[1]);
      height = (obj->sphe.texture->clipable.clip_height) * obj->sphe.y_repeat;
      width = (obj->sphe.texture->clipable.clip_width) * obj->sphe.x_repeat;
      x = width * (0.5 - (atan2(hit.z - CZ, hit.x - CX) / M_PI));
      y = height * (0.5 - (asin((hit.y - CY) / obj->sphe.rad) / M_PI));
      mat->color.full = get_texture_color(obj->sphe.texture, x, y);
    }
}
