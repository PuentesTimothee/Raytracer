/*
** useful.c for  in /home/puente_t/rendu/gfx_fdf1
**
** Made by Timothée Puentes
** Login   <puente_t@epitech.net>
**
** Started on  Mon Nov 16 16:02:29 2015 Timothée Puentes
** Last update Fri May 20 14:13:11 2016 Jean-Adrien Domage
*/

#include <stdio.h>
#include <lapin.h>
#include "raytracer1.h"

void			*printing(void *_data)
{
  t_data		*data;
  t_bunny_position	p;

  data = _data;
  p.x = 0;
  p.y = 0;
  while (data->on_off < 4)
    {
      aa_supp(data);
      if (data->cat != NULL)
	print_cat(data);
      else
	bunny_blit(&data->win->buffer, &data->actual->clipable, &p);
      bunny_display(data->win);
    }
  data->on_off = 0;
  return (NULL);
}

int		check_limits(double size, double posy, double alpha,
			     t_3d_pos nray[2])
{
  double		newy;

  newy = alpha * nray[0].y + nray[1].y;
  if (newy > posy && newy < posy + size)
    return (1);
  return (0);
}

char				*bunny_strcat(char *head, char *tail)
{
  int				l1;
  int				l2;
  char				*str;

  l1 = -1;
  l2 = -2;
  while (head[++l1] != 0);
  while (tail[++l2] != 0);
  if ((str = bunny_malloc(l1 + l2 + 1)) == NULL)
    return (NULL);
  l1 = -1;
  l2 = -1;
  while (head[++l1] != 0)
    str[++l2] = head[l1];
  l1 = -1;
  while (tail[++l1] != 0)
    str[++l2] = tail[l1];
  str[++l2] = 0;
  return (str);
}

void				bunny_my_fill(t_bunny_pixelarray *pix, unsigned int color)
{
  unsigned int			*buff;
  unsigned int			c;
  unsigned int			max;

  buff = pix->pixels;
  c = 0;
  max = pix->clipable.clip_height * pix->clipable.clip_width;
  while (c < max)
    {
      if (c <= max)
	buff[c] = color;
      c += 1;
    }
}

int		fdf_strcmp(const char *cs, char *ns)
{
  int		c;

  c = 0;
  while (cs[c] != 0 && ns[c] != 0)
    {
      if (cs[c] != ns[c])
	return (1);
      c += 1;
    }
  return (0);
}
