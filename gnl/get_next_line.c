/*
** get_next_line.c for  in /home/puente_t/rendu/CPE_2015_getnextline
**
** Made by puente_t
** Login   <puente_t@epitech.net>
**
** Started on  Wed Jan  6 17:24:43 2016 puente_t
** Last update Tue May 10 14:25:55 2016 Timothée Puentes
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "get_next_line.h"

char		*add_to_str(char *dest, char *ori)
{
  int		size;
  char		*tmp;

  size = my_len(dest);
  if ((tmp = my_strdup(dest)) == NULL)
    return (NULL);
  if (dest != NULL)
    bunny_free(dest);
  size += my_len(ori);
  if ((dest = bunny_malloc(size + 1)) == NULL)
    return (NULL);
  dest[0] = 0;
  my_strcat(dest, tmp);
  my_strcat(dest, ori);
  bunny_free(tmp);
  return (dest);
}

int		check(char *str)
{
  int		c;

  if (str == NULL)
    return (0);
  c = -1;
  while (str[++c] != 0)
    if (str[c] == '\n')
      break;
  if (str[c] == '\n')
    {
      c += 1;
      return (c);
    }
  return (0);
}

char		*gnlbis(char *str)
{
  if (str[0] == 0)
    return (NULL);
  if ((str = stock(str, 1)) == NULL)
    return (NULL);
  return (str);
}

char		*get_next_line(const int fd)
{
  char		*str;
  char		*buffer;
  char		sorted;
  int		readed;

  str = NULL;
  if ((str = stock(str, 0)) == NULL)
    return (NULL);
  readed = READ_SIZE;
  sorted = check(str);
  while (!sorted && readed == READ_SIZE)
    {
      if ((buffer = bunny_malloc(READ_SIZE + 1)) == NULL)
	return (NULL);
      if ((readed = read(fd, buffer, READ_SIZE)) == -1)
	return (NULL);
      buffer[readed] = 0;
      if ((str = add_to_str(str, buffer)) == NULL)
	return (NULL);
      bunny_free(buffer);
      sorted = check(str);
    }
  return (gnlbis(str));
}
