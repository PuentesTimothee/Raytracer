/*
** aa_supp.c for  in /home/puente_t/rendu/Info/gfx_raytracer2
**
** Made by Timothée Puentes
** Login   <puente_t@epitech.net>
**
** Started on  Thu May 12 11:19:11 2016 Timothée Puentes
** Last update Thu May 12 12:22:26 2016 Timothée Puentes
*/

#include "raytracer1.h"

static t_color		getpixel(t_bunny_pixelarray *pix,
				 t_bunny_position *pos)
{
  unsigned int		*buff;
  int			c;
  t_color		color;

  color.full = BLACK;
  c = pos->x + (pix->clipable.clip_width * pos->y);
  buff = pix->pixels;
  if (pos->y < PIX_H && pos->y >= 0 && pos->x >= 0 && pos->x < PIX_W)
    color.full = buff[c];
  return (color);
}

static t_color		get_color_sample(t_data *data,
					 t_bunny_position *p)
{
  t_bunny_position	pos;
  t_3d_pos		color;
  t_color		actcolor;

  actcolor.full = BLACK;
  color.x = 0;
  color.y = 0;
  color.z = 0;
  pos.y = p->y * AA_SAMPLE;
  while (pos.y < p->y * AA_SAMPLE + AA_SAMPLE)
    {
      pos.x = p->x * AA_SAMPLE;
      while (pos.x < p->x * AA_SAMPLE + AA_SAMPLE)
	{
	  color.x += getpixel(data->pix, &pos).argb[0];
	  color.y += getpixel(data->pix, &pos).argb[1];
	  color.z += getpixel(data->pix, &pos).argb[2];
	  pos.x += 1;
	}
      pos.y += 1;
    }
  actcolor.argb[0] = color.x / (double)(AA_SAMPLE * AA_SAMPLE);
  actcolor.argb[1] = color.y / (double)(AA_SAMPLE * AA_SAMPLE);
  actcolor.argb[2] = color.z / (double)(AA_SAMPLE * AA_SAMPLE);
  return (actcolor);
}

void			aa_supp(t_data *data)
{
  t_bunny_position	pos;
  t_color		color;

  pos.x = 0;
  while (pos.x < WIN_X)
    {
      pos.y = 0;
      while (pos.y < WIN_Y)
	{
	  color = get_color_sample(data, &pos);
	  tekpixel(data->actual, &pos, &color);
	  pos.y += 1;
	}
      pos.x += 1;
    }
}
