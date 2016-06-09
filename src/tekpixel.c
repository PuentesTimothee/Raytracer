/*
** test-LibLapin.c for  in /home/puente_t/Test
**
** Made by Timothée Puentes
** Login   <puente_t@epitech.net>
**
** Started on  Thu Oct 15 12:55:32 2015 Timothée Puentes
** Last update Thu May 19 15:32:58 2016 Timothée Puentes
*/

#include <lapin.h>
#include "raytracer1.h"

void			tekpixel(t_bunny_pixelarray *pix,
				 t_bunny_position *pos,
				 t_color *color)
{
  unsigned int		*buff;
  int			c;

  c = pos[0].x + (pix->clipable.clip_width * pos[0].y);
  buff = pix->pixels;
  if (pos->y < pix->clipable.clip_height && pos->y >= 0)
    if (pos->x >= 0 && pos->x < pix->clipable.clip_width)
      buff[c] = color->full;
}

void			tekpixel_t(t_bunny_pixelarray *pix,
				   t_bunny_position *pos,
				   t_color *color)
{
  t_color		old;
  unsigned int		*buff;
  int			c;
  double		pe;

  if (pos->y > pix->clipable.clip_height || pos->y < 0)
    return ;
  if (pos->x < 0 || pos->x > pix->clipable.clip_width)
    return ;
  c = pos[0].x + (pix->clipable.clip_width * pos[0].y);
  buff = pix->pixels;
  old.full = buff[c];
  pe = color->argb[3] / (double)255;
  old.argb[0] = color->argb[0] * pe + old.argb[0] * (1 - pe);
  old.argb[1] = color->argb[1] * pe + old.argb[1] * (1 - pe);
  old.argb[2] = color->argb[2] * pe + old.argb[2] * (1 - pe);
  buff[c] = old.full;
}
