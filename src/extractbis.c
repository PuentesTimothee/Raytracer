/*
** extractbis.c for  in /home/puente_t/rendu/Info/gfx_raytracer1
**
** Made by Timothée Puentes
** Login   <puente_t@epitech.net>
**
** Started on  Mon Feb 15 16:46:04 2016 Timothée Puentes
** Last update Mon May  2 17:55:01 2016 Timothée Puentes
*/

#include <lapin.h>
#include <math.h>
#include <stdio.h>
#include "raytracer1.h"

int			extract_cylibis(t_bunny_ini *file, t_data *data,
					int idx, const char *scope)
{
  const char		*str;

  if ((str = bunny_ini_get_field(file, scope, "radius", 0)) == NULL)
   return (print_error("No Cylinder radius\n"));
  data->obj[idx].cyli.rad = const_atoi(str);
  if ((str = bunny_ini_get_field(file, scope, "size", 0)) == NULL)
    return (print_error("No Cylinder size\n"));
  data->obj[idx].cyli.size = const_atoi(str);
  if ((str = bunny_ini_get_field(file, scope, "color", 0)) == NULL)
    return (print_error("No Cylinder color\n"));
  data->obj[idx].cyli.mat.color.full = hex_to_color(str);
  if ((str = bunny_ini_get_field(file, scope, "shine", 0)) == NULL)
   return (print_error("No Cylinder shinness\n"));
  data->obj[idx].cyli.mat.shine = const_atoi(str) * 2;
  if ((str = bunny_ini_get_field(file, scope, "reflection", 0)) == NULL)
   return (print_error("No Cylinder reflection\n"));
  data->obj[idx].cyli.mat.reflect = const_atoi(str) / (double)100;
  if (add_translation(file, scope, &data->obj[idx].cyli.pos))
    return (print_error("No Cylinder Trasnlation position\n"));
  return (0);
}

int			extract_cyli(t_bunny_ini *file, t_data *data,
				     int idx, const char *scope)
{
  const char		*str;

  data->obj[idx].cyli.type = CYLINDER;
  if ((str = bunny_ini_get_field(file, scope, "pos", 0)) == NULL)
    return (print_error("No Cylinder position in x\n"));
  data->obj[idx].cyli.pos.x = const_atoi(str);
  if ((str = bunny_ini_get_field(file, scope, "pos", 1)) == NULL)
   return (print_error("No Cylinder position in y\n"));
  data->obj[idx].cyli.pos.y = const_atoi(str);
  if ((str = bunny_ini_get_field(file, scope, "pos", 2)) == NULL)
   return (print_error("No Cylinder position in z\n"));
  data->obj[idx].cyli.pos.z = const_atoi(str);
  if ((str = bunny_ini_get_field(file, scope, "rot", 0)) == NULL)
    return (print_error("No Cylinder rotation in x\n"));
  data->obj[idx].cyli.rot.x = const_atoi(str) * DEG_TO_RAD;
  if ((str = bunny_ini_get_field(file, scope, "rot", 1)) == NULL)
    return (print_error("No Cylinder rotation in y\n"));
  data->obj[idx].cyli.rot.y = const_atoi(str) * DEG_TO_RAD;
  if ((str = bunny_ini_get_field(file, scope, "rot", 2)) == NULL)
    return (print_error("No Cylinder rotation in z\n"));
  data->obj[idx].cyli.rot.z = const_atoi(str) * DEG_TO_RAD;
  return (extract_cylibis(file, data, idx, scope));
}

int			extract_conebis(t_bunny_ini *file, t_data *data,
				     int idx, const char *scope)
{
  const char		*str;

  if ((str = bunny_ini_get_field(file, scope, "size", 0)) == NULL)
    return (print_error("No Cone size\n"));
  data->obj[idx].cone.size = const_atoi(str);
  if ((str = bunny_ini_get_field(file, scope, "color", 0)) == NULL)
    return (print_error("No Cone color\n"));
  data->obj[idx].cone.mat.color.full = hex_to_color(str);
  if ((str = bunny_ini_get_field(file, scope, "open", 0)) == NULL)
    return (print_error("No Cone open variable\n"));
  data->obj[idx].cone.open = const_atoi(str);
  if ((str = bunny_ini_get_field(file, scope, "shine", 0)) == NULL)
    return (print_error("No Cone shinness\n"));
  data->obj[idx].cone.mat.shine = const_atoi(str) * 2;
  if ((str = bunny_ini_get_field(file, scope, "reflection", 0)) == NULL)
    return (print_error("No Cone reflection\n"));
  data->obj[idx].cone.mat.reflect = const_atoi(str) / (double)100;
  if (add_translation(file, scope, &data->obj[idx].cone.pos))
    return (print_error("No Cone Trasnlation position\n"));
  return (0);
}

int			extract_cone(t_bunny_ini *file, t_data *data,
				     int idx, const char *scope)
{
  const char		*str;

  data->obj[idx].cone.type = CONE;
  if ((str = bunny_ini_get_field(file, scope, "rot", 0)) == NULL)
    return (print_error("No Cone rotation in x\n"));
  data->obj[idx].cone.rot.x = const_atoi(str) * DEG_TO_RAD;
  if ((str = bunny_ini_get_field(file, scope, "rot", 1)) == NULL)
    return (print_error("No Cone rotation in y\n"));
  data->obj[idx].cone.rot.y = const_atoi(str) * DEG_TO_RAD;
  if ((str = bunny_ini_get_field(file, scope, "rot", 2)) == NULL)
    return (print_error("No Cone rotation in z\n"));
  data->obj[idx].cone.rot.z = const_atoi(str) * DEG_TO_RAD;
  if ((str = bunny_ini_get_field(file, scope, "pos", 0)) == NULL)
    return (print_error("No Cone position in y\n"));
  data->obj[idx].cone.pos.x = const_atoi(str);
  if ((str = bunny_ini_get_field(file, scope, "pos", 1)) == NULL)
    return (print_error("No Cone postition in y\n"));
  data->obj[idx].cone.pos.y = const_atoi(str);
  if ((str = bunny_ini_get_field(file, scope, "pos", 2)) == NULL)
    return (print_error("No Cone positition in y\n"));
  data->obj[idx].cone.pos.z = const_atoi(str);
  return (extract_conebis(file, data, idx, scope));
}
