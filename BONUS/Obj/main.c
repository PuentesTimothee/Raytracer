/*
** main.c for Obj in /home/aragon_m/modules/Infographie/gfx_raytracer2/BONUS/Obj
** 
** Made by My-Lan Aragon
** Login   <aragon_m@epitech.net>
** 
** Started on  Wed Apr 27 13:01:42 2016 My-Lan Aragon
** Last update Mon May  9 16:29:06 2016 My-Lan Aragon
*/

#include <lapin.h>
#include "my.h"

int	main(int ac, char **av)
{
  if (ac != 2)
    return (my_perror("Usage : ./raytracer2 file.obj.\n"));
  load_obj(av[1]);
  return (0);
}
