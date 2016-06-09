/*
** extractter.c for  in /home/puente_t/rendu/Info/gfx_raytracer2
**
** Made by Timothée Puentes
** Login   <puente_t@epitech.net>
**
** Started on  Thu Apr 14 12:09:10 2016 Timothée Puentes
** Last update Thu May 19 14:10:04 2016 Timothée Puentes
*/

#include <stdio.h>
#include <lapin.h>
#include <math.h>
#include "raytracer1.h"

int			add_translation(t_bunny_ini *file,
					const char *scope, t_3d_pos *pos)
{
  t_3d_pos		new;
  const char		*str;

  if ((str = bunny_ini_get_field(file, scope, "trans", 0)) == NULL)
    return (0);
  if ((new.x = const_atoi(str)) < 0 ||
      (str = bunny_ini_get_field(file, scope, "trans", 1)) == NULL ||
      (new.y = const_atoi(str)) < 0 ||
      (str = bunny_ini_get_field(file, scope, "trans", 2)) == NULL ||
      (new.z = const_atoi(str)) < 0)
    return (1);
  pos->x += new.x;
  pos->y += new.y;
  pos->z += new.z;
  return (0);
}

int			extract_light(t_bunny_ini *file, t_data *data,
				      int idx, const char *scope)
{
  const char		*str;

  if ((str = bunny_ini_get_field(file, scope, "light_pos", 0)) == NULL)
   return (print_error("No Light position in x\n"));
  data->light[idx].pos.x = const_atoi(str);
  if (add_translation(file, scope, &data->obj[idx].plan.pos))
    return (print_error("No Trasnlation position\n"));
  if ((str = bunny_ini_get_field(file, scope, "light_pos", 1)) == NULL)
    return (print_error("No Light position in y\n"));
  data->light[idx].pos.y = const_atoi(str);
  if ((str = bunny_ini_get_field(file, scope, "light_pos", 2)) == NULL)
   return (print_error("No Light position in z\n"));
  data->light[idx].pos.z = const_atoi(str);
  if ((str = bunny_ini_get_field(file, scope, "ambient", 0)) == NULL)
    return (print_error("No Light ambient color\n"));
  data->light[idx].mat.color.full = hex_to_color(str);
  if ((str = bunny_ini_get_field(file, scope, "shade", 0)) == NULL)
    return (print_error("No Light intensity\n"));
  data->light[idx].mat.shade = const_atoi(str);
  if (data->light[idx].mat.shade == 0)
    data->light[idx].mat.shade = 1;
  if (add_translation(file, scope, &data->light[idx].pos))
    return (print_error("No Light Trasnlation position\n"));
  return (0);
}

int			extract_cam(t_bunny_ini *file, t_data *data)
{
  const char		*str;

  if ((str = bunny_ini_get_field(file, "Scene", "cam_pos", 0)) == NULL)
    return (print_error("No Camera position in x\n"));
  data->cam.cam_pos.x = const_atoi(str);
  if ((str = bunny_ini_get_field(file, "Scene", "cam_pos", 1)) == NULL)
    return (print_error("No Camera position in y\n"));
  data->cam.cam_pos.y = const_atoi(str);
  if ((str = bunny_ini_get_field(file, "Scene", "cam_pos", 2)) == NULL)
    return (print_error("No Camera position in z\n"));
  data->cam.cam_pos.z = const_atoi(str);
  if (add_translation(file, "Scene", &data->cam.cam_pos))
    return (print_error("No Trasnlation position\n"));
  if ((str = bunny_ini_get_field(file, "Scene", "cam_rot", 0)) == NULL)
    return (print_error("No Camerea rotation in x\n"));
  data->cam.cam_rot.x = const_atoi(str) * DEG_TO_RAD;
  if ((str = bunny_ini_get_field(file, "Scene", "cam_rot", 1)) == NULL)
    return (print_error("No Camera rotation in y\n"));
  data->cam.cam_rot.y = const_atoi(str) * DEG_TO_RAD;
  if ((str = bunny_ini_get_field(file, "Scene", "cam_rot", 2)) == NULL)
    return (print_error("No camera rotation in z\n"));
  data->cam.cam_rot.z = const_atoi(str) * DEG_TO_RAD;
  return (0);
}

static int		extract_cube_bis(t_bunny_ini *file, t_data *data,
					 int idx, const char *scope)
{
  const char		*str;

  data->obj[idx].cube.type = CUBE;
  if ((str = bunny_ini_get_field(file, scope, "color", 0)) == NULL)
    return (print_error("No Cube color\n"));
  data->obj[idx].cube.mat.color.full = hex_to_color(str);
  if ((str = bunny_ini_get_field(file, scope, "shine", 0)) == NULL)
   return (print_error("No Cube shinness\n"));
  data->obj[idx].cube.mat.shine = const_atoi(str) * 2;
  if ((str = bunny_ini_get_field(file, scope, "reflection", 0)) == NULL)
   return (print_error("No Cube reflection\n"));
  data->obj[idx].cube.mat.reflect = const_atoi(str) / (double)100;
  if (add_translation(file, scope, &data->obj[idx].cube.pos))
    return (print_error("No Cube Trasnlation position\n"));
  return (0);
}

int			extract_cube(t_bunny_ini *file, t_data *data,
				     int idx, const char *scope)
{
  const char		*str;

  data->obj[idx].cube.type = CUBE;
  if ((str = bunny_ini_get_field(file, scope, "rot", 0)) == NULL)
    return (print_error("No Cube rotation x\n"));
  data->obj[idx].cube.rot.x = const_atoi(str) * DEG_TO_RAD;
  if ((str = bunny_ini_get_field(file, scope, "rot", 1)) == NULL)
    return (print_error("No Cube rotation y\n"));
  data->obj[idx].cube.rot.y = const_atoi(str) * DEG_TO_RAD;
  if ((str = bunny_ini_get_field(file, scope, "rot", 2)) == NULL)
    return (print_error("No Cube rotation z\n"));
  data->obj[idx].cube.rot.z = const_atoi(str) * DEG_TO_RAD;
  if ((str = bunny_ini_get_field(file, scope, "pos", 0)) == NULL)
    return (print_error("No Cube position x\n"));
  data->obj[idx].cube.pos.x = const_atoi(str);
  if ((str = bunny_ini_get_field(file, scope, "pos", 1)) == NULL)
    return (print_error("No Cube position y\n"));
  data->obj[idx].cube.pos.y = const_atoi(str);
  if ((str = bunny_ini_get_field(file, scope, "pos", 2)) == NULL)
    return (print_error("No Cube position z\n"));
  data->obj[idx].cube.pos.z = const_atoi(str);
  if ((str = bunny_ini_get_field(file, scope, "size", 0)) == NULL)
    return (print_error("No Cube Size\n"));
  data->obj[idx].cube.size = const_atoi(str);
  return (extract_cube_bis(file, data, idx, scope));
}
