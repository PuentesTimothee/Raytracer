/*
** calc_cylinder.c for  in /home/puente_t/rendu/Info/gfx_raytracer2
**
** Made by Timothée Puentes
** Login   <puente_t@epitech.net>
**
** Started on  Wed May 18 13:03:42 2016 Timothée Puentes
** Last update Wed May 18 17:36:56 2016 Timothée Puentes
*/

#include <lapin.h>
#include <math.h>
#include <stdio.h>
#include "raytracer1.h"

t_3d_pos	get_normale_cyl(t_3d_pos *nray, double alpha,
				t_3d_pos *rot, t_3d_pos *pos)
{
  t_3d_pos	normale;

  normale.y = pos->y;
  normale.x = (nray[0].x * alpha + nray[1].x);
  normale.z = (nray[0].z * alpha + nray[1].z);
  normale = rev_matrice(&normale, rot);
  return (normale);
}

double		check_cap(t_3d_pos *nray,
			  t_3d_pos *pos,
			  double size,
			  double rad)
{
  t_3d_pos	new;
  double	alpha;

  if (nray[0].y == 0)
    return (-1);
  alpha = (size - nray[1].y) / nray[0].y;
  new.x = nray[0].x * alpha + nray[1].x;
  new.z = nray[0].z * alpha + nray[1].z;
  if (pow(new.x - pos->x, 2) + pow(new.z - pos->z, 2) - rad * rad < 0)
    return (alpha);
  return (-1);
}

static t_3d_pos	calc_eq(t_3d_pos *ray, t_3d_pos *pos, int radius)
{
  t_3d_pos	eq;

  eq.x = pow(ray[0].x, 2) + pow(ray[0].z, 2);
  eq.y = ray[0].x * ray[1].x + ray[0].z * ray[1].z;
  eq.y += -ray[0].x * pos->x - ray[0].z * pos->z;
  eq.y *= 2;
  eq.z = pow(ray[1].x - pos->x, 2) + pow(ray[1].z - pos->z, 2);
  eq.z += -radius * radius;
  return (eq);
}

void		treat_cap(t_cylinder *cyli, t_3d_pos *nray,
			  t_inter *inter, t_3d_pos *pos)
{
  double	alpha[2];

  alpha[0] = check_cap(nray, pos, pos->y + cyli->size, cyli->rad);
  alpha[1] = check_cap(nray, pos, pos->y, cyli->rad);
  if (alpha[0] > 0 && (alpha[0] < inter->alpha || inter->alpha < 0))
    *inter = set_inter(alpha[0], cyli->mat, NORMAL_CAP);
  if (alpha[1] > 0 && (alpha[1] < inter->alpha || inter->alpha < 0))
    *inter = set_inter(alpha[1], cyli->mat, NORMAL_CAP);
}

void		alpha_cylinder(t_obj *obj, t_3d_pos *ray,
			       t_inter *inter)
{
  double	alpha[2];
  double	delta;
  t_3d_pos	eq;
  t_3d_pos	pos;
  t_3d_pos	nray[2];

  pos = three_matrice(&obj->cyli.pos, &obj->cyli.rot);
  nray[0] = three_matrice(&ray[0], &obj->cyli.rot);
  nray[1] = three_matrice(&ray[1], &obj->cyli.rot);
  eq = calc_eq(&nray[0], &pos, obj->cyli.rad);
  delta = eq.y * eq.y - 4 * eq.x * eq.z;
  if (delta > 0 && eq.x != 0)
    {
      alpha[0] = (-eq.y + sqrt(delta)) / (double)(2 * eq.x);
      alpha[1] = (-eq.y - sqrt(delta)) / (double)(2 * eq.x);
      if (check_limits(obj->cyli.size, pos.y, alpha[0], &nray[0])
	  && alpha[0] > 0 && (alpha[0] < inter->alpha || inter->alpha < 0))
	*inter = set_inter(alpha[0], obj->cyli.mat, NORMAL_CYL(0));
      if (check_limits(obj->cyli.size, pos.y, alpha[1], &nray[0]) &&
	  alpha[1] > 0 && (alpha[1] < inter->alpha || inter->alpha < 0))
	*inter = set_inter(alpha[1], obj->cyli.mat, NORMAL_CYL(1));
    }
  treat_cap(&obj->cyli, nray, inter, &pos);
}
