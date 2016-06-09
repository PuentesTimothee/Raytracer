/*
** useful_load_cat.c for gfx_raytracer2 in /home/domage_j/rendu/TODO/gfx_raytracer2/src
**
** Made by domage jean-adrien
** Login   <domage_j@epitech.net>
**
** Started on  Sun May 15 11:48:10 2016 domage jean-adrien
** Last update Sun May 22 11:54:49 2016 Jean-Adrien Domage
*/

#include <lapin.h>
#include "raytracer1.h"

void			init_cat(t_data *data)
{
  t_bunny_position	pos;
  t_color		color;

  color.full = BLACK;
  pos.x = 0;
  pos.y = 0;
  if ((data->cat = bunny_load_picture("sprite/cat.png")) == NULL)
    return ;
  if ((data->black = bunny_new_pixelarray(data->size.x, data->size.y)) == NULL)
    return ;
  while (pos.x < data->size.x)
    {
      while (pos.y < data->size.y)
	{
	  tekpixel(data->black, &pos, &color);
	  pos.y += 1;
	}
      pos.y = 0;
      pos.x += 1;
    }
}
