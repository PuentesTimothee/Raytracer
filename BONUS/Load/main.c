/*
** main.c<BONUS/Load> for  in /home/puente_t/rendu/Info/Info_Test/gfx_paint_tmp
**
** Made by Timothée Puentes
** Login   <puente_t@epitech.net>
**
** Started on  Wed Jan 20 11:13:28 2016 Timothée Puentes
** Last update Wed Jan 20 11:21:43 2016 Timothée Puentes
*/

#include <stdio.h>
#include <lapin.h>
#include <unistd.h>
#include <fcntl.h>
#include "load.h"

t_bunny_pixelarray	*arrayh_32bit(int pic,
				      t_bitheader header,
				      t_bunny_pixelarray *pix)
{
  t_bunny_position	p;
  unsigned char		arg[4];
  unsigned int		c;
  t_color		act;
  unsigned int		*buff;

  buff = pix->pixels;
  p.y = header.height - 1;
  while (p.y >= 0)
    {
      p.x = 0;
      while (p.x < header.width)
	{
	  read(pic, arg, 4);
	  act.argb[0] = arg[2];
	  act.argb[1] = arg[1];
	  act.argb[2] = arg[0];
	  act.argb[3] = arg[3];
	  c = p.x + (pix->clipable.clip_width * p.y);
	  buff[c] = act.full;
	  p.x++;
	}
      p.y--;
    }
  return (pix);
}

t_bunny_pixelarray	*arrayh_24bit(int pic,
				      t_bitheader header,
				      t_bunny_pixelarray *pix)
{
  t_bunny_position	p;
  unsigned char		arg[4];
  unsigned int		c;
  t_color		act;
  unsigned int		*buff;

  buff = pix->pixels;
  p.y = header.height - 1;
  while (p.y >= 0)
    {
      p.x = 0;
      while (p.x < header.width - 1)
	{
	  read(pic, arg, 3);
	  act.argb[0] = arg[2];
	  act.argb[1] = arg[1];
	  act.argb[2] = arg[0];
	  act.argb[3] = 255;
	  c = p.x + (pix->clipable.clip_width * p.y);
	  buff[c] = act.full;
	  p.x++;
	}
      p.y--;
    }
  return (pix);
}

t_bunny_pixelarray	*load_bitmap(const char *file)
{
  t_bunny_pixelarray	*pix;
  t_bitheader		header;
  int			fd;

  if ((fd = open(file, O_RDONLY)) < 0)
    return (NULL);
  if (read(fd, &header, sizeof(t_bitheader)) != sizeof(t_bitheader))
    return (NULL);
  if ((pix = bunny_new_pixelarray(header.width, header.height)) == NULL)
    return (NULL);
  if (header.byte_pix == 32)
    pix = arrayh_32bit(fd, header, pix);
  else if (header.byte_pix == 24)
    pix = arrayh_24bit(fd, header, pix);
  else
    return (NULL);
  close(fd);
  return (pix);
}

t_bunny_response	mainloop(void *_win)
{
  t_bunny_window	*win;
  t_bunny_pixelarray	*pix;
  t_bunny_position	p;

  p.x = 0;
  p.y = 0;
  win = _win;
  if ((pix = load_bitmap("image_eleve.bmp")) == NULL)
    return (EXIT_FAILURE);
  bunny_blit(&win->buffer, &pix->clipable, &p);
  bunny_delete_clipable(&pix->clipable);
  bunny_display(win);
  return (GO_ON);
}

int			main(void)
{
  t_bunny_window	*win;

  win = bunny_start(1024, 1024, false, "LOAD");
  bunny_set_loop_main_function(mainloop);
  bunny_loop(win, 150, win);
  return (0);
}
