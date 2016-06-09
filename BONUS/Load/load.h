/*
** load.h for  in /home/puente_t/rendu/Info/Info_Test/gfx_paint_tmp
**
** Made by Timothée Puentes
** Login   <puente_t@epitech.net>
**
** Started on  Wed Jan 20 11:11:17 2016 Timothée Puentes
** Last update Mon Jan 25 10:15:00 2016 Timothée Puentes
*/

#ifndef LOAD_H_
# define LOAD_H_

typedef struct	s_bitheader
{
  char		type[2];
  int		size;
  int		empty;
  int		offset;
  int		size_head;
  int		width;
  int		height;
  short		nb_bit;
  short		byte_pix;
  int		compress;
  int		bytesize;
  int		ppi_y;
  int		ppi_x;
  int		palette_size;
  int		imp_color;
}		__attribute__((packed)) t_bitheader;

#endif /* !LOAD_H_ */
