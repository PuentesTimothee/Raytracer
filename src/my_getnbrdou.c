/*
** my_getnbrdou.c for Obj in /home/aragon_m/modules/Infographie/gfx_raytracer2/BONUS/Obj
**
** Made by My-Lan Aragon
** Login   <aragon_m@epitech.net>
**
** Started on  Fri May  6 21:27:27 2016 My-Lan Aragon
** Last update Thu May 19 14:15:47 2016 Timothée Puentes
*/

#include <stdlib.h>
#include "raytracer1.h"

static int	verify_str(char *s)
{
  int		i;
  int		vir;

  i = 0;
  vir = 0;
  if (s == NULL)
    return (-1);
  if (s[i] == '-')
    i = i + 1;
  while (s[i] != '\0')
    {
      if (s[i] == '.' && i != 0)
	vir = vir + 1;
      else if (s[i] > '9' || s[i] < '0' || vir > 1 || s[i] == '.')
	return (-1);
      i = i + 1;
    }
  return (0);
}

double		my_getnbrdou(char *s)
{
  double	nb;
  int		i;
  int		j;

  i = 0;
  nb = 0;
  j = 10;
  if (s[i] == '-')
    i = i + 1;
  if (verify_str(s) == -1)
    {
      my_perror(s);
      return (my_perror(W_NUM));
    }
  while (s[i] != '\0' && (s[i] >= '0' && s[i] <= '9'))
    nb = nb * 10 + s[i++] - '0';
  if (s[i] != '.')
    return (nb);
  while (s[++i] != '\0')
    {
      nb = nb + (double)(s[i] - '0') / j;
      j = j * 10;
    }
  return (s[0] == '-' ? -nb : nb);
}

unsigned int	my_getnbr(char *s)
{
  unsigned int 	nb;
  int		i;

  nb = 0;
  i = 0;
  while (s[i] >= '0' && s[i] <= '9')
    {
      nb = nb * 10 + s[i] - '0';
      i = i + 1;
    }
  if (i == 0)
    {
      my_perror(W_NUM);
      return (0);
    }
  return (nb);
}
