/*
** gnl2.c for  in /home/puente_t/rendu/PSU/PSU_2015_tetris
**
** Made by Timothée Puentes
** Login   <puente_t@epitech.net>
**
** Started on  Fri Mar  4 16:38:30 2016 Timothée Puentes
** Last update Tue May 10 14:24:20 2016 Timothée Puentes
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "get_next_line.h"

char		*mystrcpy(char *dest, const char *src)
{
  int		c;

  c = 0;
  if (dest == NULL || src == NULL)
    return (dest);
  while (src[c] != 0)
    {
      dest[c] = src[c];
      c++;
    }
  dest[c] = 0;
  return (dest);
}

int		my_len(const char *str)
{
  int		n;

  if (str == NULL)
    return (0);
  n = 0;
  while (str[n] != '\0')
    n++;
  return (n);
}

char		*mystrncpy(char *dest, const char *src, int n)
{
  int		c;

  c = 0;
  while (src[c] != '\0' && n > c)
    {
      dest[c] = src[c];
      c++;
    }
  dest[c] = '\0';
  return (dest);
}

int		check_stock(char *str)
{
  int		c;

  if (str == NULL)
    return (0);
  c = -1;
  while (str[++c] != 0)
    if (str[c] == '\n')
      break;
  return (c);
}

char		*stock(char *new, int mode)
{
  static char	*dump = NULL;
  char		*exit;
  int		c;

  if (mode == 0)
    {
      if ((new = my_strdup(dump)) == NULL)
	return (NULL);
      if (dump != NULL)
	bunny_free(dump);
      dump = NULL;
      return (new);
    }
  if ((c = check_stock(new)) <= 0)
    c = 0;
  if ((exit = my_strndup(new, c)) == NULL)
    return (NULL);
  c = check_stock(new);
  if ((dump = my_strdup(&new[GET_STOCK])) == NULL)
    return (NULL);
  bunny_free(new);
  return (exit);
}
