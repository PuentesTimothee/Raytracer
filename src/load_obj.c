/*
** load_obj.c for Obj in /home/aragon_m/modules/Infographie/gfx_raytracer2/BONUS/Obj
**
** Made by My-Lan Aragon
** Login   <aragon_m@epitech.net>
**
** Started on  Mon May  2 11:05:19 2016 My-Lan Aragon
** Last update Thu May 19 15:29:47 2016 My-Lan Aragon
*/

#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "raytracer1.h"
#include "get_next_line.h"

int		recup_obj(t_triangle *tri, char *path, t_fctn *tab_fct)
{
  char		**tab;
  char		*s;
  int		fd;
  int		i;

  if ((fd = open(path, O_RDONLY)) == -1)
    return (my_perror(OPEN_F));
  while ((s = get_next_line(fd)) != NULL)
    {
      i = -1;
      if ((tab = my_str_to_wordtab(s, " ")) == NULL)
	return (my_perror(MALLOC_F));
      while (++i != 3)
	if (my_strcmp(tab_fct[i].s, tab[0]) == 0 && my_tablen(tab) >= 4)
	  if (tab_fct[i].fct(tri, tab) == -1)
	    return (-1);
      bunny_free(s);
    }
  return (0);
}

int		load_obj(char *path, t_triangle *tri)
{
  t_fctn	tab_fct[2];

  initial(tab_fct);
  if (initial_tri(tri) == -1)
    return (-1);
  if (recup_obj(tri, path, tab_fct) == -1)
    return (-1);
  if (calc_vnorm(tri) == -1)
    return (-1);
  return (0);
}
