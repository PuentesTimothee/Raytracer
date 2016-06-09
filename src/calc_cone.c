/*
** calc_sphere.c for  in /home/puente_t/rendu/Info/gfx_raytracer1
**
** Made by Timothée Puentes
** Login   <puente_t@epitech.net>
**
** Started on  Tue Feb  9 12:59:58 2016 Timothée Puentes
** Last update Tue May 10 11:41:36 2016 Timothée Puentes
*/

#include <lapin.h>
#include <math.h>
#include <stdio.h>
#include "raytracer1.h"

t_3d_pos	get_normale_cone(t_3d_pos *nray, double alpha,
				 t_3d_pos *rot, t_3d_pos *pos)
{
  t_3d_pos	normale;

  normale.y = 0;
  normale.x = (nray[0].x * alpha + nray[1].x);
  normale.x -= pos->x;
  normale.z = (nray[0].z * alpha + nray[1].z);
  normale.z -= pos->z;
  normale = rev_matrice(&normale, rot);
  return (normale);
}

t_3d_pos	get_normale_cap(t_3d_pos *rot)
{
  t_3d_pos	normale;

  normale.x = 0;
  normale.y = 1;
  normale.z = 0;
  normale = rev_matrice(&normale, rot);
  return (normale);
}

static t_3d_pos	calc_eq(t_3d_pos *ray, t_3d_pos *pos, int open)
{
  t_3d_pos	eq;

  eq.x = pow(ray[0].x, 2) + pow(ray[0].z, 2) - open * pow(ray[0].y, 2);
  eq.y = ray[0].x * ray[1].x + ray[0].z * ray[1].z;
  eq.y += - open * ray[0].y * ray[1].y;
  eq.y += -ray[0].x * pos->x - ray[0].z * pos->z - -open * ray[0].y * pos->y;
  eq.y *= 2;
  eq.z = pow(ray[1].x - pos->x, 2) + pow(ray[1].z - pos->z, 2);
  eq.z += -open * pow(ray[1].y - pos->y, 2);
  return (eq);
}

void		alpha_cone(t_obj *obj, t_3d_pos *ray,
			   t_inter *inter)
{
  double	alpha[2];
  double	delta;
  t_3d_pos	eq;
  t_3d_pos	pos;
  t_3d_pos	nray[2];

  pos = three_matrice(&obj->cone.pos, &obj->cone.rot);
  nray[0] = three_matrice(&ray[0], &obj->cone.rot);
  nray[1] = three_matrice(&ray[1], &obj->cone.rot);
  eq = calc_eq(&nray[0], &pos, OPEN);
  delta = eq.y * eq.y - 4 * eq.x * eq.z;
  if (delta > MIN && eq.x != 0)
    {
      alpha[0] = (-eq.y + sqrt(delta)) / (double)(2 * eq.x);
      alpha[1] = (-eq.y - sqrt(delta)) / (double)(2 * eq.x);
      if (check_limits(obj->cone.size, pos.y, alpha[1], nray))
	if (alpha[0] > 0 && (alpha[0] < inter->alpha || inter->alpha < 0))
	  *inter = set_inter(alpha[0], obj->cone.mat, NORMAL_CON(0));
      if (check_limits(obj->cone.size, pos.y, alpha[1], nray))
	if (alpha[1] > 0 && (alpha[1] < inter->alpha || inter->alpha < 0))
	  *inter = set_inter(alpha[1], obj->cone.mat, NORMAL_CON(1));
    }
  alpha[0] = check_cap(nray, &pos, pos.y + OSIZ, OSIZ * sqrt(OPEN));
  if (alpha[0] > 0 && (alpha[0] < inter->alpha || inter->alpha < 0))
    *inter = set_inter(alpha[0], obj->cone.mat, NORMAL_OCAP);
}
