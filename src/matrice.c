/*
** matrice.c for  in /home/puente_t/rendu/Info/gfx_raytracer1
**
** Made by Timothée Puentes
** Login   <puente_t@epitech.net>
**
** Started on  Mon Feb 15 17:47:12 2016 Timothée Puentes
** Last update Wed May 18 15:17:59 2016 Timothée Puentes
*/

#include <lapin.h>
#include <math.h>
#include "raytracer1.h"

t_3d_pos	matrice_rot_x(t_3d_pos *pos,
			      double angle)
{
  t_3d_pos	new;

  new.x = pos->x;
  new.y = pos->y * cos(angle) - pos->z * sin(angle);
  new.z = pos->y * sin(angle) + pos->z * cos(angle);
  return (new);
}

t_3d_pos	matrice_rot_y(t_3d_pos *pos,
			      double angle)
{
  t_3d_pos	new;

  new.x = pos->x * cos(angle) + pos->z * sin(angle);
  new.y = pos->y;
  new.z = -pos->x * sin(angle) + pos->z * cos(angle);
  return (new);
}

t_3d_pos	matrice_rot_z(t_3d_pos *pos,
			      double angle)
{
  t_3d_pos	new;

  new.x = pos->x * cos(angle) - pos->y * sin(angle);
  new.y = pos->x * sin(angle) + pos->y * cos(angle);
  new.z = pos->z;
  return (new);
}

t_3d_pos	three_matrice(t_3d_pos *ori,
			      t_3d_pos *rot)
{
  t_3d_pos	new;

  if (ori == NULL)
    {
      new.x = 0;
      new.y = 0;
      new.z = 0;
      return (new);
    }
  new = *ori;
  if (rot == NULL)
    return (new);
  if (rot->x != 0)
    new = matrice_rot_x(&new, rot->x);
  if (rot->z != 0)
    new = matrice_rot_z(&new, rot->z);
  if (rot->y != 0)
    new = matrice_rot_y(&new, rot->y);
  return (new);
}

t_3d_pos	rev_matrice(t_3d_pos *ori,
			    t_3d_pos *rot)
{
  t_3d_pos	new;

  if (ori == NULL)
    {
      new.x = 0;
      new.y = 0;
      new.z = 0;
      return (new);
    }
  new = *ori;
  if (rot == NULL)
    return (new);
  new = matrice_rot_y(&new, -rot->y);
  new = matrice_rot_z(&new, -rot->z);
  new = matrice_rot_x(&new, -rot->x);
  return (new);
}
