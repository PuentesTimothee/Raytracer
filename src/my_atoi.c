/*
** my_atoi.c<gfx_raytracer1> for  in /home/puente_t/rendu/Info/gfx_raytracer1
**
** Made by Timothée Puentes
** Login   <puente_t@epitech.net>
**
** Started on  Thu Feb  4 15:44:42 2016 Timothée Puentes
** Last update Tue May 10 14:11:30 2016 Timothée Puentes
*/

#include <lapin.h>
#include "raytracer1.h"

int		my_power_it(int nb, int power)
{
  int		c;
  int		result;

  c = 0;
  result = 1;
  while (c != power)
    {
      result = result * nb;
      c += 1;
    }
  return (result);
}

unsigned int	hex_to_color(const char *s)
{
  int		hexdigit;
  int		i;
  unsigned int	n;

  i = 0;
  if (s[i] == '0')
    if (s[++i] == 'x' || s[i] == 'X')
       i += 1;
  n = 0;
  while (s[i] != 0 && i <= 10)
    {
      if (s[i] >= '0' && s[i] <= '9')
	hexdigit = s[i] - '0';
      else if (s[i] >= 'A' && s[i] <= 'F')
	hexdigit = s[i] - 'A' + 10;
      n = 16 * n + hexdigit;
      i += 1;
    }
  if (i == 8)
    return (n + BLACK);
  else if (i == 10)
    return (n);
  return (WHITE);
}

int		const_atoi(const char *str)
{
  int		c;
  int		result;
  int		size;
  int		neg;

  neg = 0;
  c = 0;
  result = 0;
  size = 0;
  if (str[0] == 0)
    return (0);
  while ((str[size] == '-' && size == 0) || IS_N(str[size]))
      size += 1;
  if (str[0] == '-')
    neg = 1;
  while (size - c - 1 >= neg)
    {
      result = result + (my_power_it(10, c) * (str[size - c - 1] - '0'));
      c += 1;
    }
  if (str[0] == '-')
    result = result * -1;
  return (result);
}
