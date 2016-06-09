/*
** basic.c for Obj in /home/aragon_m/modules/Infographie/gfx_raytracer2/BONUS/Obj
** 
** Made by My-Lan Aragon
** Login   <aragon_m@epitech.net>
** 
** Started on  Wed Apr 27 13:02:38 2016 My-Lan Aragon
** Last update Fri May  6 22:17:42 2016 My-Lan Aragon
*/

#include <unistd.h>
#include <stdlib.h>
#include "my.h"

int	my_strlen(char *str)
{
  int	i;

  i = 0;
  if (str == NULL)
    return (i);
  while (str[i] != '\0')
    i = i + 1;
  return (i);
}

int	my_perror(char *str)
{
  write(2, str, my_strlen(str));
  return (-1);
}

int	my_strcmp(char *s1, char *s2)
{
  int	i;

  i = 0;
  if (my_strlen(s1) != my_strlen(s2))
    return (-1);
  while (s1[i] != '\0' && s2[i] != '\0')
    {
      if (s1[i] != s2[i])
	return (-1);
      i = i + 1;
    }
  return (0);
}

int	my_tablen(char **tab)
{
  int	i;

  i = 0;
  if (tab == NULL)
    return (i);
  while (tab[i] != NULL)
    i = i + 1;
  return (i);
}
