/*
** save_bmp.c for  in /home/puente_t/rendu/Info/Info_Test/gfx_paint_tmp
**
** Made by puente_t
** Login   <puente_t@epitech.net>
**
** Started on  Thu Jan 14 12:12:31 2016 puente_t
** Last update Thu Apr 21 14:44:23 2016 Timothée Puentes
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <lapin.h>
#include <unistd.h>
#include <fcntl.h>
#include "raytracer1.h"

t_bitheader		fill_header(t_data *data)
{
  t_bitheader		header;

  header.type[0] = 0x42;
  header.type[1] = 0x4D;
  header.offset = 54;
  header.size_head = 40;
  header.height = data->pix->clipable.clip_height;
  header.width = data->pix->clipable.clip_width;
  header.size = 32 * header.width * header.height + 50;
  header.nb_bit = 1;
  header.byte_pix = 32;
  header.compress = 0;
  header.bytesize = 4 * header.width * header.height;
  header.ppi_x = 2834;
  header.ppi_y = 2834;
  header.palette_size = 0;
  header.imp_color = 0;
  return (header);
}

int			fill_bmp(t_bitheader header, int fd, t_data *data)
{
  t_ini			save_bmp;

  save_bmp.buff = data->pix->pixels;
  save_bmp.c = header.width * header.height - 1;
  save_bmp.p.y = header.height - 1;
  while (save_bmp.p.y >= 0)
    {
      save_bmp.p.x = 0;
      while (save_bmp.p.x < header.width)
	{
	  save_bmp.c = save_bmp.p.x + (header.width * save_bmp.p.y);
	  save_bmp.act.full = save_bmp.buff[save_bmp.c];
	  save_bmp.arg[2] = save_bmp.act.argb[0];
	  save_bmp.arg[1] = save_bmp.act.argb[1];
	  save_bmp.arg[0] = save_bmp.act.argb[2];
	  save_bmp.arg[3] = save_bmp.act.argb[3];
	  if (write(fd, save_bmp.arg, 4) != 4)
	    return (1);
	  save_bmp.p.x++;
	}
      save_bmp.p.y--;
    }
  return (0);
}

int			save_bitmap(const char *file, t_data *data)
{
  t_bitheader		header;
  int			fd;
  mode_t		mode;

  mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
  if ((fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, mode)) < 0)
    return (1);
  header = fill_header(data);
  if (write(fd, &header, sizeof(t_bitheader)) != sizeof(t_bitheader))
    return (1);
  if (fill_bmp(header, fd, data) == 1)
    return (1);
  close(fd);
  return (0);
}
