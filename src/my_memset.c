/*
** my_memset.c for Obj in /home/aragon_m/modules/Infographie/gfx_raytracer2/BONUS/Obj
** 
** Made by My-Lan Aragon
** Login   <aragon_m@epitech.net>
** 
** Started on  Sun May  8 01:27:45 2016 My-Lan Aragon
** Last update Sun May  8 02:33:29 2016 My-Lan Aragon
*/

#include <stdlib.h>

void		*my_memset(void *s, int c, size_t n)
{
  size_t       	i;
  unsigned char	*str;

  i = 0;
  str = s;
  while (i != n)
    {
      str[i] = c;
      i = i + 1;
    }
  return (str);
}
