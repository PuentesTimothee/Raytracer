/*
** extract.c for  in /home/puente_t/rendu/Info/gfx_raytracer1
**
** Made by Timothée Puentes
** Login   <puente_t@epitech.net>
**
** Started on  Sun Feb 14 11:59:17 2016 Timothée Puentes
** Last update Sun May 22 11:47:22 2016 Jean-Adrien Domage
*/

#include <lapin.h>
#include <math.h>
#include <stdio.h>
#include "raytracer1.h"

int		extract_spherebis(t_bunny_ini	*file,
				  t_data	*data,
				  int		idx,
				  const char	*scope)
{
  const char	*str;

  if ((str = bunny_ini_get_field(file, scope, "texture", 0)) == NULL)
    {
      PATH = NULL;
      TEXTURE = NULL;
    }
  else
    {
      PATH = bunny_strdup(str);
      if (!(TEXTURE = bunny_load_pixelarray(PATH)))
	return (print_error("The texture was not found!\n"));
      if ((str = bunny_ini_get_field(file, scope, "x_repeat", 0)) == NULL)
	return (print_error("No texture x_repeat attribut !\n"));
      data->obj[idx].sphe.x_repeat = const_atoi(str);
      if ((str = bunny_ini_get_field(file, scope, "y_repeat", 0)) == NULL)
	return (print_error("No texture y_repeat attribut !\n"));
      data->obj[idx].sphe.y_repeat = const_atoi(str);
    }
  if ((str = bunny_ini_get_field(file, scope, "effect", 0)) == NULL)
    PATH = NULL;
  PATH = bunny_dup(str);
  if (add_translation(file, scope, &data->obj[idx].sphe.pos))
    return (print_error("No Sphere Trasnlation position\n"));
  return (0);
}

int			extract_sphere(t_bunny_ini *file, t_data *data,
				       int idx, const char *scope)
{
  const char		*str;

  if ((str = bunny_ini_get_field(file, scope, "pos", 0)) == NULL)
    return (print_error("No Sphere position in x\n"));
  data->obj[idx].sphe.pos.x = const_atoi(str);
  if ((str = bunny_ini_get_field(file, scope, "pos", 1)) == NULL)
    return (print_error("No Sphere position in y\n"));
  data->obj[idx].sphe.pos.y = const_atoi(str);
  if ((str = bunny_ini_get_field(file, scope, "pos", 2)) == NULL)
    return (print_error("No Sphere position in z\n"));
  data->obj[idx].sphe.pos.z = const_atoi(str);
  if ((str = bunny_ini_get_field(file, scope, "radius", 0)) == NULL)
    return (print_error("No Sphere radius\n"));
  data->obj[idx].sphe.rad = const_atoi(str);
  if ((str = bunny_ini_get_field(file, scope, "color", 0)) == NULL)
    return (print_error("No Sphere color\n"));
  data->obj[idx].sphe.mat.color.full = hex_to_color(str);
  if ((str = bunny_ini_get_field(file, scope, "shine", 0)) == NULL)
    return (print_error("No Sphere shinness\n"));
  data->obj[idx].sphe.mat.shine = 2 * const_atoi(str);
  if ((str = bunny_ini_get_field(file, scope, "reflection", 0)) == NULL)
    return (print_error("No Sphere reflection\n"));
  data->obj[idx].sphe.mat.reflect = const_atoi(str) / (double)100;
  data->obj[idx].sphe.type = SPHERE;
  return (extract_spherebis(file, data, idx, scope));
}

int			extract_planbis(t_bunny_ini *file, t_data *data,
					int idx, const char *scope)
{
  const char *str;

  if ((str = bunny_ini_get_field(file, scope, "color", 0)) == NULL)
    return (print_error("No Plan primary color\n"));
  data->obj[idx].plan.mat.color.full = hex_to_color(str);
  if ((str = bunny_ini_get_field(file, scope, "color_2", 0)) == NULL)
    SECONDARY = data->obj[idx].plan.mat.color.full;
  else
    SECONDARY = hex_to_color(str);
  if ((str = bunny_ini_get_field(file, scope, "shine", 0)) == NULL)
   return (print_error("No Plan shinness\n"));
  data->obj[idx].plan.mat.shine = 2 * const_atoi(str);
  if ((str = bunny_ini_get_field(file, scope, "reflection", 0)) == NULL)
    return (print_error("No Plan reflection\n"));
  data->obj[idx].plan.mat.reflect = const_atoi(str) / (double)100;
  if (add_translation(file, scope, &data->obj[idx].plan.pos))
    return (print_error("No Plan Trasnlation position\n"));
  return (0);
}

int			extract_plan(t_bunny_ini *file, t_data *data,
				     int idx, const char *scope)
{
  const char		*str;

  data->obj[idx].plan.type = PLAN;
  if ((str = bunny_ini_get_field(file, scope, "rotation", 0)) == NULL)
    return (print_error("No Plan rotation in x\n"));
  data->obj[idx].plan.rot.x = const_atoi(str) * DEG_TO_RAD;
  if ((str = bunny_ini_get_field(file, scope, "rotation", 1)) == NULL)
    return (print_error("No Plan rotation in y\n"));
  data->obj[idx].plan.rot.y = const_atoi(str) * DEG_TO_RAD;
  if ((str = bunny_ini_get_field(file, scope, "rotation", 2)) == NULL)
    return (print_error("No Plan rotation in z\n"));
  data->obj[idx].plan.rot.z = const_atoi(str) * DEG_TO_RAD;
  if ((str = bunny_ini_get_field(file, scope, "pos", 0)) == NULL)
    return (print_error("No Plan position\n"));
  data->obj[idx].plan.pos.x = const_atoi(str);
  if ((str = bunny_ini_get_field(file, scope, "pos", 0)) == NULL)
    return (print_error("No Plan position\n"));
  data->obj[idx].plan.pos.y = const_atoi(str);
  if ((str = bunny_ini_get_field(file, scope, "pos", 0)) == NULL)
    return (print_error("No Plan position\n"));
  data->obj[idx].plan.pos.z = const_atoi(str);
  if (extract_planter(file, data, idx, scope) != 0)
    return (1);
  return (extract_planbis(file, data, idx, scope));
}
