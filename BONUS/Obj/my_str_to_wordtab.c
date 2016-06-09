/*
** my_str_to_wordtab.c for Obj in /home/aragon_m/modules/Infographie/gfx_raytracer2/BONUS/Obj
** 
** Made by My-Lan Aragon
** Login   <aragon_m@epitech.net>
** 
** Started on  Mon May  2 11:52:58 2016 My-Lan Aragon
** Last update Sun May  8 00:35:02 2016 My-Lan Aragon
*/

#include <stdlib.h>
#include "lapin.h"
#include "my.h"

int	is_delim(char *delim, char c)
{
  int	i;

  i = 0;
  while (delim[i] != '\0')
    {
      if (delim[i] == c)
	return (0);
      i = i + 1;
    }
  return (1);
}

int	count_word(char *str, char *delim)
{
  int	i;
  int	nb_word;

  nb_word = 0;
  i = 0;
  while (str[i] != '\0')
    {
      if (is_delim(delim, str[i]) == 1)
	{
	  nb_word = nb_word + 1;
	  while (is_delim(delim, str[i + 1]) == 1 && str[i + 1] != '\0')
	    i = i + 1;
	}
      i = i + 1;
    }
  return (nb_word);
}

int	fill_let(char *str, char *delim, int index)
{
  int	nb_let;

  nb_let = 0;
  if (is_delim(delim, str[index]) == 0)
    while (is_delim(delim, str[index]) == 0)
      index = index + 1;
  while ((is_delim(delim, str[index])) == 1 && str[index] != '\0')
    {
      index = index + 1;
      nb_let = nb_let + 1;
    }
  return (nb_let);
}

char	**fill_tab(char **tab, char *str, char *delim, int nb_word)
{
  int	i;
  int	j;
  int	index;
  int	nb_let;

  index = 0;
  i = -1;
  while (++i < nb_word)
    {
      j = -1;
      nb_let = fill_let(str, delim, index);
      if ((tab[i] = bunny_malloc(sizeof(char) * (nb_let + 1))) == NULL)
	 return (NULL);
      while (++j < nb_let)
	{
	  if (is_delim(delim, str[index]) == 0)
	    while (is_delim(delim, str[index]) == 0)
	      index = index + 1;
	  tab[i][j] = str[index];
	  index = index + 1;
	}
      tab[i][j] = '\0';
    }
  tab[i] = NULL;
  return (tab);
}

char	**my_str_to_wordtab(char *str, char *delim)
{
  char	**tab;
  int	nb_word;

  if (str == NULL)
    return (NULL);
  nb_word = count_word(str, delim);
  if ((tab = bunny_malloc(sizeof(char *) * (nb_word + 1))) == NULL)
    return (NULL);
  if (fill_tab(tab, str, delim, nb_word) == NULL)
    return (NULL);
  return (tab);
}
