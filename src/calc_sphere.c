/*
** calc_sphere.c for  in /home/puente_t/rendu/Info/gfx_raytracer1
**
** Made by Timothée Puentes
** Login   <puente_t@epitech.net>
**
** Started on  Tue Feb  9 12:59:58 2016 Timothée Puentes
** Last update Fri May 20 12:16:12 2016 Timothée Puentes
*/

#include <lapin.h>
#include <math.h>
#include <stdio.h>
#include "raytracer1.h"

t_inter		set_inter(double alpha, t_mat mat,
			  t_3d_pos normale)
{
  t_inter	new;

  new.alpha = alpha;
  new.mat = mat;
  new.normal = normale;
  return (new);
}

static double	calc_b(t_3d_pos *ray, t_obj *obj)
{
  double	b;

  b = ray[0].x * ray[1].x + ray[0].y * ray[1].y + ray[0].z * ray[1].z;
  b += -ray[0].x * CX - ray[0].y * CY - ray[0].z * CZ;
  b *= 2;
  return (b);
}

static double	calc_c(t_3d_pos *ray, t_obj *obj)
{
  double	c;

  c = pow(ray[1].x, 2) + pow(ray[1].y, 2) + pow(ray[1].z, 2);
  c += -ray[1].x * CX * 2 - ray[1].y * CY * 2 - ray[1].z * CZ * 2;
  c += pow(CX, 2) + pow(CY, 2) + pow(CZ, 2) - RAD * RAD;
  return (c);
}

void		alpha_sphere(t_obj *obj, t_3d_pos *ray,
			     t_inter *inter)
{
  double	alpha[2];
  double	delta;
  t_3d_pos	eq;
  t_mat		mat;

  eq.x = pow(ray[0].x, 2) + pow(ray[0].y, 2) + pow(ray[0].z, 2);
  if (eq.x < MIN)
    return ;
  eq.y = calc_b(ray, obj);
  eq.z = calc_c(ray, obj);
  delta = eq.y * eq.y - 4 * eq.x * eq.z;
  if (delta > MIN)
    {
      alpha[0] = (-eq.y + sqrt(delta)) / (double)(2 * eq.x);
      alpha[1] = (-eq.y - sqrt(delta)) / (double)(2 * eq.x);
      mat = obj->sphe.mat;
      alpha[0] = ((alpha[0] < alpha[1]) ? (alpha[0]) : (alpha[1]));
      sphere_texturing(obj, ray, alpha[0], &mat);
      if (alpha[0] > MIN &&
	  (alpha[0] < inter->alpha || inter->alpha < MIN))
	*inter = set_inter(alpha[0], mat, NORMS(0));
    }
}
