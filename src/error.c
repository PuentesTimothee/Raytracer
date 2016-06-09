/*
** error.c for  in /home/puente_t/rendu/Info/gfx_raytracer2
**
** Made by Timothée Puentes
** Login   <puente_t@epitech.net>
**
** Started on  Fri Apr 15 10:10:28 2016 Timothée Puentes
** Last update Tue May  3 11:04:25 2016 Timothée Puentes
*/

#include <lapin.h>
#include <unistd.h>
#include "raytracer1.h"

void		*print_error_pnt(char *str)
{
  write(2, str, my_strlen(str));
  return (NULL);
}

int		print_error(char *str)
{
  write(2, str, my_strlen(str));
  return (1);
}
