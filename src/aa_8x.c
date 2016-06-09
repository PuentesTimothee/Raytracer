/*
** aa_8x.c for  in /home/puente_t/rendu/Info/gfx_raytracer2/src
**
** Made by Timothée Puentes
** Login   <puente_t@epitech.net>
**
** Started on  Wed Apr 20 10:16:10 2016 Timothée Puentes
** Last update Wed May 18 13:03:28 2016 Timothée Puentes
*/

#include <stdio.h>
#include <lapin.h>
#include "raytracer1.h"

static unsigned char	getpixel(t_bunny_pixelarray *pix,
				 int posx,
				 int posy,
				 int n)
{
  unsigned int		*buff;
  int			c;
  t_color		color;

  color.full = BLACK;
  c = posx + (pix->clipable.clip_width * posy);
  buff = pix->pixels;
  if (posy <= PIX_H && posy >= 0 && posx >= 0 && posx <= PIX_W)
    color.full = buff[c];
  return (color.argb[n]);
}

static t_color		getfullpixel(t_bunny_pixelarray *pix,
				     t_bunny_position *pos)
{
  unsigned int		*buff;
  int			c;
  t_color		color;

  color.full = BLACK;
  c = pos->x + (pix->clipable.clip_width * pos->y);
  buff = pix->pixels;
  if (pos->y <= PIX_H && pos->y >= 0 && pos->x >= 0 && pos->x <= PIX_W)
    color.full = buff[c];
  return (color);
}

static unsigned int	get_around_color(t_bunny_pixelarray *pix,
					 const t_bunny_position *pos,
					 int n)
{
  unsigned int		cmp;

  cmp = 0;
  if (pos->x != 0 && pos->y != 0)
    cmp += getpixel(pix, pos->x - 1, pos->y - 1, n);
  if (pos->x != 0)
    cmp += getpixel(pix, pos->x - 1, pos->y, n);
  if (pos->y != 0)
    cmp += getpixel(pix, pos->x, pos->y - 1, n);
  if (pos->y != 0 && pos->x + 1 != PIX_W)
    cmp += getpixel(pix, pos->x + 1, pos->y - 1, n);
  if (pos->x != 0 && pos->y + 1 != PIX_H)
    cmp += getpixel(pix, pos->x - 1, pos->y + 1, n);
  if (pos->x + 1 != PIX_W && pos->y + 1 != PIX_H)
    cmp += getpixel(pix, pos->x + 1, pos->y + 1, n);
  if (pos->x + 1 != PIX_W)
    cmp += getpixel(pix, pos->x + 1, pos->y, n);
  if (pos->y + 1 != PIX_H)
    cmp += getpixel(pix, pos->x, pos->y + 1, n);
  return (cmp);
}

static void		aa_at_pixel(t_bunny_pixelarray *pix,
				    t_bunny_pixelarray *pix_tmp,
				    const t_bunny_position *pos)
{
  double		total;
  t_color		color;
  int			n;
  t_bunny_position	p;

  total = 8;
  if (pos->x == 0 || pos->x == PIX_W - 1)
    total -= 3;
  if (pos->y == 0 || pos->y == PIX_H - 1)
    total -= ((total == 8) ? (3) : (2));
  n = 0;
  while (n < 4)
    {
      color.argb[n] = get_around_color(pix, pos, n) / (2 * total)
	+ getpixel(pix, pos->x, pos->y, n) / 2;
      n += 1;
    }
  p.x = pos->x;
  p.y = pos->y;
  tekpixel(pix_tmp, &p, &color);
}

void			aa_8x(t_bunny_pixelarray *pix,
			      t_bunny_pixelarray *pix_tmp)
{
  t_bunny_position	p;
  t_color		color;

  p.y = -1;
  while (++p.y < PIX_H)
    {
      p.x = 0;
      while (p.x < PIX_W)
	{
	  aa_at_pixel(pix, pix_tmp, &p);
	  p.x += 1;
	}
    }
  p.y = 0;
  while (p.y < PIX_H)
    {
      p.x = 0;
      while (p.x < PIX_W)
	{
	  color = getfullpixel(pix_tmp, &p);
	  tekpixel(pix, &p, &color);
	  p.x += 1;
	}
      p.y += 1;
    }
}
