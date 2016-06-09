/*
** extract_plan.c for rt2 in /home/domage_j/rendu/TODO/gfx_raytracer2/src
**
** Made by domage jean-adrien
** Login   <domage_j@epitech.net>
**
** Started on  Sun May  1 18:17:17 2016 domage jean-adrien
** Last update Mon May  2 19:14:54 2016 Timothée Puentes
*/

#include <stdio.h>
#include <lapin.h>
#include "raytracer1.h"

int		extract_planter(t_bunny_ini	*file,
				t_data		*data,
				int		idx,
				const char	*scope)
{
  const char	*str;

  if ((str = bunny_ini_get_field(file, scope, "texture", 0)) == NULL)
    {
      P_PATH = NULL;
      P_TEXTURE = NULL;
    }
  else
    {
      P_PATH = bunny_strdup(str);
      if ((P_TEXTURE = bunny_load_pixelarray(P_PATH)) == NULL)
	return (print_error("The texture was not found!\n"));
    }
  return (0);
}
