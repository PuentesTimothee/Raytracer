/*
** calc_plan.c for  in /home/puente_t/rendu/Info/gfx_raytracer1/src
**
** Made by Timothée Puentes
** Login   <puente_t@epitech.net>
**
** Started on  Thu Feb 18 12:55:27 2016 Timothée Puentes
** Last update Tue May 10 11:42:32 2016 Timothée Puentes
*/

#include <lapin.h>
#include <stdio.h>
#include "raytracer1.h"

static t_3d_pos		set_normale(double x, double y, double z)
{
  t_3d_pos	       new;

  new.x = x;
  new.y = y;
  new.z = z;
  return (new);
}

static void		check_one(t_obj *obj, double *inter,
				  t_3d_pos *nray, t_3d_pos *norm)
{
  double		a;
  t_3d_pos		hit;

  if (nray[0].x == 0)
    nray[0].x = 1;
  a = (obj->cube.pos.x - nray[1].x) / nray[0].x;
  hit = find_hit(a, &nray[0], &nray[1]);
  if ((*inter < MIN || (a < *inter && a > MIN)) &&
      obj->cube.pos.y < hit.y && hit.y <= obj->cube.pos.y + obj->cube.size &&
      obj->cube.pos.z < hit.z && hit.z <= obj->cube.pos.z + obj->cube.size)
    {
      *inter = a;
      *norm = set_normale(1, 0, 0);
    }
  a = (obj->cube.pos.x + obj->cube.size - nray[1].x) / nray[0].x;
  hit = find_hit(a, &nray[0], &nray[1]);
  if ((*inter < MIN || (a < *inter && a > MIN)) &&
      obj->cube.pos.y < hit.y && hit.y <= obj->cube.pos.y + obj->cube.size &&
      obj->cube.pos.z < hit.z && hit.z <= obj->cube.pos.z + obj->cube.size)
    {
      *inter = a;
      *norm = set_normale(-1, 0, 0);
    }
}

static void		check_two(t_obj *obj, double *inter,
				  t_3d_pos *nray, t_3d_pos *norm)
{
  double		a;
  t_3d_pos		hit;

  if (nray[0].y == 0)
    nray[0].y = 1;
  a = (obj->cube.pos.y - nray[1].y) / nray[0].y;
  hit = find_hit(a, &nray[0], &nray[1]);
  if ((*inter < MIN || (a < *inter && a > MIN)) &&
      obj->cube.pos.x < hit.x && hit.x <= obj->cube.pos.x + obj->cube.size &&
      obj->cube.pos.z < hit.z && hit.z <= obj->cube.pos.z + obj->cube.size)
    {
      *inter = a;
      *norm = set_normale(0, 1, 0);
    }
  a = (obj->cube.pos.y + obj->cube.size - nray[1].y) / nray[0].y;
  hit = find_hit(a, &nray[0], &nray[1]);
  if ((*inter < MIN ||
       (a < *inter && a > MIN)) && obj->cube.pos.x < hit.x &&
      hit.x <= obj->cube.pos.x + obj->cube.size &&
      obj->cube.pos.z < hit.z && hit.z <= obj->cube.pos.z + obj->cube.size)
    {
      *inter = a;
      *norm = set_normale(0, -1, 0);
    }
}

static void		check_three(t_obj *obj, double *inter,
				    t_3d_pos *nray, t_3d_pos *norm)
{
  double		a;
  t_3d_pos		hit;

  if (nray[0].z == 0)
    nray[0].z = 1;
  a = (obj->cube.pos.z - nray[1].z) / nray[0].z;
  hit = find_hit(a, &nray[0], &nray[1]);
  if ((*inter < MIN || (a < *inter && a > MIN)) &&
      obj->cube.pos.y < hit.y && hit.y <= obj->cube.pos.y + obj->cube.size &&
      obj->cube.pos.x < hit.x && hit.x <= obj->cube.pos.x + obj->cube.size)
    {
      *inter = a;
      *norm = set_normale(0, 0, -1);
    }
  a = (obj->cube.pos.z + obj->cube.size - nray[1].z) / nray[0].z;
  hit = find_hit(a, &nray[0], &nray[1]);
  if ((*inter < MIN || (a < *inter && a > MIN)) &&
      obj->cube.pos.y < hit.y && hit.y <= obj->cube.pos.y + obj->cube.size &&
      obj->cube.pos.x < hit.x && hit.x <= obj->cube.pos.x + obj->cube.size)
    {
      *inter = a;
      *norm = set_normale(0, 0, 1);
    }
}

void			alpha_cube(t_obj *obj, t_3d_pos *ray,
				   t_inter *inter)
{
  t_3d_pos	nray[2];
  double	alpha;
  t_3d_pos	normal;

  nray[0] = three_matrice(&ray[0], &obj->cube.rot);
  nray[1] = three_matrice(&ray[1], &obj->cube.rot);
  alpha = -1;
  check_one(obj, &alpha, nray, &normal);
  check_two(obj, &alpha, nray, &normal);
  check_three(obj, &alpha, nray, &normal);
  if (alpha > MIN && (alpha < inter->alpha || inter->alpha == -1))
    {
      inter->mat = obj->cube.mat;
      inter->alpha = alpha;
      inter->normal = rev_matrice(&normal, &obj->cube.rot);
    }
}
