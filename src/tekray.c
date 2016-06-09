/*
** tekray.c for  in /home/puente_t/rendu/Info/gfx_raytracer1
**
** Made by Timothée Puentes
** Login   <puente_t@epitech.net>
**
** Started on  Wed Feb  3 14:22:06 2016 Timothée Puentes
** Last update Thu May 12 15:09:30 2016 Timothée Puentes
*/

#include <lapin.h>
#include "raytracer1.h"

void		tekray(const t_bunny_position *pos_on_screen,
		       t_3d_pos *ray, t_data *data)
{
  ray->z = WIN_X;
  ray->x = AAWIN_X / 2 - pos_on_screen->x;
  ray->y = AAWIN_Y / 2 - pos_on_screen->y;
}
