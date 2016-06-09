/*
** get_next_line.c for get_next_line in /home/aragon_m/modules/Prog_Elem/CPE_2015_getnextline
** 
** Made by My-Lan Aragon
** Login   <aragon_m@epitech.net>
** 
** Started on  Wed Jan  6 10:48:50 2016 My-Lan Aragon
** Last update Sun May  8 03:06:35 2016 My-Lan Aragon
*/

#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "my.h"
#include "lapin.h"
#include "get_next_line.h"

int	slen(char *s)
{
  int	i;

  i = 0;
  if (s == NULL)
    return (i);
  while (s[i] != '\0')
    i = i + 1;
  return (i);
}

char	*cpy_dup(char *dest, char *src, int size)
{
  char	*temp;
  int	i;
  int	j;

  j = -1;
  i = 0;
  if (src == NULL ||
      ((temp = bunny_malloc(sizeof(char) * (size + 1 + slen(dest)))) == NULL))
      return (NULL);
  if (dest != NULL)
    while (i < slen(dest))
      {
	temp[i] = dest[i];
	i = i + 1;
      }
  while (++j < size)
    {
      temp[i] = src[j];
      i = i + 1;
    }
  temp[i] = '\0';
  bunny_free(src);
  bunny_free(dest);
  return (temp);
}

char	*fill_save(char *buffer, int save_point, int read_oct)
{
  char	*temp;
  int	i;

  i = 0;
  save_point = save_point + 1;
  if ((temp = bunny_malloc(sizeof(char) * (read_oct - save_point + 2))) == NULL)
    return (NULL);
  my_memset(temp, 0, read_oct - save_point + 2);
  while (save_point <= read_oct)
    {
      temp[i] = buffer[save_point];
      i = i + 1;
      save_point = save_point + 1;
    }
  temp[i] = '\0';
  return (temp);
}

char	*verify_buff(char *line, char **save_str, int fd, int *read_oct)
{
  char	*buffer;
  int	i;

  i = 0;
  if ((buffer = bunny_malloc(sizeof(char) * (READ_SIZE + 1))) == NULL)
    return (NULL);
  while (*read_oct != 0)
    {
      i = -1;
      if ((*read_oct = read(fd, buffer, READ_SIZE)) == -1)
	return (NULL);
      buffer[*read_oct] = '\0';
      while (++i < *read_oct)
	if (buffer[i] == '\n')
	  {
	    if ((!(line = cpy_dup(line, buffer, i)))
		|| ((*read_oct - i > 0 && fd != 0)
		    && (*save_str = fill_save(buffer, i, *read_oct)) == NULL))
	      return (NULL);
	    return (line);
	  }
      if ((line = cpy_dup(line, buffer, i)) == NULL)
	return (NULL);
    }
  return (line);
}

char		*get_next_line(const int fd)
{
  char		*l;
  int		i;
  int		read_oct;
  static char	*sv;

  read_oct = 1;
  l = NULL;
  if ((i = -1) == -1 && sv != NULL)
    {
      while (sv[++i] != '\0')
	if (sv[i] == '\n' || (sv[i] == '\0' && read_oct == 0))
	  {
	    if (!(l = cpy_dup(l, sv, i)) || !(sv = fill_save(sv, i, slen(sv))))
	      return (NULL);
	    return (l);
	  }
      if ((l = cpy_dup(l, sv, slen(sv))) == NULL)
	return (NULL);
    }
  if ((l = verify_buff(l, &sv, fd, &read_oct)) && read_oct != 0)
    return (l);
  if ((l = cpy_dup(NULL, l, slen(l))) && !l[0] && !read_oct)
    l = NULL;
  sv = NULL;
  return (l);
}
