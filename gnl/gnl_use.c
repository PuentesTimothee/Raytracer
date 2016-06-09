/*
** gnl_use.c for  in /home/puente_t/rendu/CPE/CPE_2015_Lemin
OB**
** Made by Timothée Puentes
** Login   <puente_t@epitech.net>
**
** Started on  Sun Apr 24 16:46:22 2016 Timothée Puentes
** Last update Tue May 10 14:11:41 2016 Timothée Puentes
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "get_next_line.h"

char	*my_strcat(char *dest, const char *src)
{
  int	c;
  char	*end_dest;

  c = 0;
  if (dest == NULL || src == NULL)
    return (dest);
  while (dest[c] != '\0')
    c++;
  end_dest = dest + c;
  c = 0;
  while (src[c] !='\0')
    {
      end_dest[c] = src[c];
      c++;
    }
  end_dest[c] = '\0';
  return (dest);
}

char	*my_strdup(const char *src)
{
  char	*dest;
  int	lenght;

  if (src == (char *)-1)
    return (NULL);
  if (src == NULL)
    {
      if ((dest = bunny_malloc(1)) == NULL)
	return (NULL);
      dest[0] = 0;
      return (dest);
    }
  lenght = my_len(src) + 1;
  if ((dest = bunny_malloc(lenght)) == NULL)
    return (NULL);
  mystrcpy(dest, src);
  return (dest);
}

char	*my_strncat(char *dest, const char *src, int nb)
{
  int	c;
  char	*end_dest;

  end_dest = dest + nb;
  c = 0;
  while (src[c] != '\0')
    {
      end_dest[c] = src[c];
      c++;
    }
  while (dest[c] != '\0')
    {
      end_dest[c] = '\0';
      c++;
    }
  end_dest[c] = '\0';
  return (dest);
}

char	*my_strndup(const char *src, int n)
{
  char	*dest;

  if ((dest = bunny_malloc(n + 1)) == NULL)
    return (NULL);
  mystrncpy(dest, src, n);
  return (dest);
}
