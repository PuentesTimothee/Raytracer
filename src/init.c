/*
** init.c for $ in /home/puente_t/rendu/Info/gfx_raytracer1
**
** Made by Timothée Puentes
** Login   <puente_t@epitech.net>
**
** Started on  Tue Feb  2 16:44:09 2016 Timothée Puentes
** Last update Sun May 22 12:05:05 2016 Jean-Adrien Domage
*/

#include <lapin.h>
#include <stdio.h>
#include "raytracer1.h"

int			get_total_objects(t_bunny_ini *file, t_data *data)
{
  const char		*scope_name;
  t_bunny_ini_scope	*scope;
  int			c;
  int			x;

  if ((scope = bunny_ini_first(file)) == NULL)
    return (print_error("Missing scope\n"));
  c = 0;
  x = 0;
  scope_name = bunny_ini_scope_name(file, scope);
  while ((scope = bunny_ini_next(file, scope)) != LAST_SCOPE)
    {
      scope_name = bunny_ini_scope_name(file, scope);
      if (fdf_strcmp(scope_name, "Scene"))
	{
	  if (fdf_strcmp(scope_name, "Light"))
	    c += 1;
	  else
	    x += 1;
	}
    }
  if ((data->nb_obj = c) < 0 || (data->nb_light = x) <= 0)
    return (-1);
  return (1);
}

int			get_type(const char *name)
{
  if (!fdf_strcmp(name, "Sphere"))
    return (SPHERE);
  else if (!fdf_strcmp(name, "Plan"))
    return (PLAN);
  else if (!fdf_strcmp(name, "Cylinder"))
    return (CYLINDER);
  else if (!fdf_strcmp(name, "Cone"))
    return (CONE);
  else if (!fdf_strcmp(name, "Cube"))
    return (CUBE);
  else
    return (-1);
}

static int		extract_treat(t_bunny_ini *file, t_data *data,
				      const char *name, int *c)
{
  int			(*extract_[5])(t_bunny_ini *, t_data *,
				       int, const char *);

  extract_[SPHERE] = extract_sphere;
  extract_[PLAN] = extract_plan;
  extract_[CYLINDER] = extract_cyli;
  extract_[CONE] = extract_cone;
  extract_[CUBE] = extract_cube;
  if (fdf_strcmp(name, "Light"))
    {
      if (get_type(name) < 0)
	return (print_error("Unknow Scope name\n"));
      if ((extract_[get_type(name)](file, data, *c, name)) == 1)
	return (print_error("Failled a creation\n"));
    }
  else if ((extract_light(file, data, *c, name)) == 1)
    return (print_error("Failled a creation\n"));
  *c += 1;
  return (0);
}

int			extract(t_bunny_ini *file, t_data *data)
{
  const char		*name;
  t_bunny_ini_scope	*scope;
  int			c;
  int			x;

  data->cat = NULL;
  name = bunny_ini_get_field(file, "Scene", "width", 0);
  data->size.x = ((name == NULL) ? (DEF_WIN_X) : (const_atoi(name)));
  name = bunny_ini_get_field(file, "Scene", "height", 0);
  data->size.y = ((name == NULL) ? (DEF_WIN_Y) : (const_atoi(name)));
  if (bunny_ini_get_field(file, "Scene", "debug", 0) == NULL)
    init_cat(data);
  if ((scope = bunny_ini_first(file)) == NULL)
    return (print_error("Missing scope\n"));
  c = 0;
  x = 0;
  while ((scope = bunny_ini_next(file, scope)) != LAST_SCOPE)
    {
      name = bunny_ini_scope_name(file, scope);
      if (fdf_strcmp(name, "Scene") &&
	  extract_treat(file, data, name, LIG_OR_OBJ) != 0)
	return (print_error("Extraction failed\n"));
    }
  return (0);
}

int			init_map(const char *filename, t_data *data)
{
  t_bunny_ini		*file;

  if ((file = bunny_load_ini(filename)) == NULL ||
      (get_total_objects(file, data)) == -1 ||
      (data->obj = bunny_malloc(sizeof(t_obj) * NBOBJ)) == NULL ||
      (data->light = bunny_malloc(sizeof(t_sphere) * NBLIG)) == NULL ||
      (extract_cam(file, data)) == 1 ||
      extract(file, data) == 1)
    return (print_error("Error initialing data\n"));
  bunny_delete_ini(file);
  data->alpha[PLAN] = alpha_plan;
  data->alpha[SPHERE] = alpha_sphere;
  data->alpha[CYLINDER] = alpha_cylinder;
  data->alpha[CONE] = alpha_cone;
  data->alpha[CUBE] = alpha_cube;
  data->mode = 1;
  data->save = NULL;
  return (0);
}
