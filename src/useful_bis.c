/*
** useful_bis.c for  in /home/puente_t/rendu/Info/gfx_raytracer2
**
** Made by Timothée Puentes
** Login   <puente_t@epitech.net>
**
** Started on  Thu Apr 21 14:33:09 2016 Timothée Puentes
** Last update Thu May 19 14:12:28 2016 Timothée Puentes
*/

#include <lapin.h>
#include "raytracer1.h"

void	calc_cat_position(t_data *data, int i)
{
  if (i == 1)
    {
      CATX = 148;
      CATY = 0;
    }
  else if (i == 2)
    {
      CATX = 0;
      CATY = 100;
    }
  else if (i == 3)
    {
      CATX = 148;
      CATY = 100;
    }
  else
    {
      CATX = 0;
      CATY = 100;
    }
}

void			print_cat(t_data *data)
{
  static int		i = 0;
  t_bunny_position	pos;

  pos.x = 0;
  pos.y = 0;
  bunny_blit(&data->win->buffer, &data->black->clipable, &pos);
  pos.x = data->win->buffer.width / 2 - 74;
  pos.y = data->win->buffer.height / 2 - 50;
  data->cat->clip_width = 150;
  data->cat->clip_height = 100;
  CATX = 0;
  CATY = 0;
  calc_cat_position(data, i);
  if (i == 4)
    i = 0;
  else
    i += 1;
  bunny_blit(&data->win->buffer, data->cat, &pos);
}

void		init_vec(t_3d_pos *vec)
{
  vec->x = 0;
  vec->y = 0;
  vec->z = 0;
}

char		*bunny_strdup(const char *src)
{
  char		*dest;
  int		lenght;
  int		c;

  lenght = my_strlen(src) + 1;
  if ((dest = bunny_malloc(lenght)) == NULL)
    return (NULL);
  c = 0;
  while (src[c] != 0)
    {
      dest[c] = src[c];
      c++;
    }
  dest[c] = 0;
  return (dest);
}

void		compute_color(t_color *color,
			      t_light *light)
{
  double	intensity;
  double	specular[3];
  double	newcmp;
  int		c;

  c = 0;
  if (light->diffuse <= 0)
    light->diffuse = 0;
  if ((intensity = light->diffuse) > 1)
    intensity = 1;
  specular[0] = light->specular.x * light->totalintensity;
  specular[1] = light->specular.y * light->totalintensity;
  specular[2] = light->specular.z * light->totalintensity;
  while (c < 3)
    {
      newcmp = color->argb[c] * intensity;
      newcmp += specular[c];
      if (newcmp < 0)
	newcmp = 0;
      else if (newcmp > 255)
	newcmp = 255;
      color->argb[c] = newcmp;
      c += 1;
    }
}
