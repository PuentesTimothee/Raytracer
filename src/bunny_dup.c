/*
** my_strstr.c for rt2 in /home/domage_j/rendu/TODO/gfx_raytracer2/src
**
** Made by domage jean-adrien
** Login   <domage_j@epitech.net>
**
** Started on  Wed Apr 20 13:41:39 2016 domage jean-adrien
** Last update Mon May  9 18:09:42 2016 Timothée Puentes
*/

#include <lapin.h>
#include <stdlib.h>

char		*bunny_dup(const char *str)
{
  char	*new;
  int	i;

  i = 0;
  if (str == NULL)
    return (NULL);
  if (!(new = bunny_malloc(sizeof(str) + 1)))
    return (NULL);
  new[sizeof(str)] = '\0';
  while (str[i])
    {
      new[i] = str[i];
      i += 1;
    }
  return (new);
}
