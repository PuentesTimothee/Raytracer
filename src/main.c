/*
** main.c for  in /home/puente_t/rendu/Info/gfx_raytracer1
**
** Made by Timothée Puentes
** Login   <puente_t@epitech.net>
**
** Started on  Tue Feb  2 16:40:21 2016 Timothée Puentes
** Last update Sun May 22 23:05:28 2016 Timothée Puentes
*/

#include <stdio.h>
#include <lapin.h>
#include "raytracer1.h"

void			*calc2_1q(void *_data)
{
  t_bunny_position	pos;
  t_3d_pos		ray[2];
  t_data		*data;

  data = _data;
  pos.x = 0;
  ORI.x = data->cam.cam_pos.x;
  ORI.y = data->cam.cam_pos.y;
  ORI.z = data->cam.cam_pos.z;
  while (pos.x < AAWIN_X)
    {
      pos.y = 0;
      while (pos.y < AAWIN_Y)
	{
	  if (data->on_off <= -1)
	    return (NULL);
	  tekray(&pos, ray, data);
	  DIR = three_matrice(&DIR, &data->cam.cam_rot);
	  ray_color_tri(data->pix, data, &ray[0], &pos);
	  pos.y += 1;
	}
      pos.x += 1;
    }
  data->on_off += 1;
  return (NULL);
}

int			calc_ray(t_data *data)
{
  if (data->mode == 0)
    {
      data->cam.cam_pos.x = 0;
      data->cam.cam_pos.y = 50;
      data->cam.cam_pos.z = -175;
      data->cam.cam_rot.x = 0;
      data->cam.cam_rot.y = 0;
      data->cam.cam_rot.z = 0;
      calc2_1q(data);
    }
  else if (pthread_create(&data->p.t1, NULL, calc_1q, data) ||
	   pthread_create(&data->p.t2, NULL, calc_2q, data) ||
	   pthread_create(&data->p.t3, NULL, calc_3q, data) ||
	   pthread_create(&data->p.t4, NULL, calc_4q, data) ||
	   pthread_create(&data->p.t5, NULL, printing, data) ||
	   pthread_join(data->p.t5, NULL))
    return (6);
  aa_supp(data);
  data->on_off = 42;
  return (0);
}

t_bunny_response	mainloop(void *_data)
{
  t_data		*data;

  data = _data;
  if (data->on_off != 42 && calc_ray(data) != 0)
    return (EXIT_ON_ERROR);
  if (data->save != NULL)
    {
      if (save_bitmap(data->save, data))
	return (EXIT_ON_ERROR);
      else
	return (EXIT_ON_SUCCESS);
    }
  bunny_blit(&data->win->buffer, &data->actual->clipable, NULL);
  bunny_display(data->win);
  return (GO_ON);
}

t_bunny_response	exit_esc(t_bunny_event_state state,
				 t_bunny_keysym key,
				 void *_data)
{
  (void)_data;
  if (key == BKS_ESCAPE && state == GO_DOWN)
    return (EXIT_ON_SUCCESS);
  return (GO_ON);
}

int			main(int ac, char **av)
{
  t_data		data;

  bunny_set_maximum_ram(MEGAO * RAM);
  if (ac < 2 ||
      (init_map(av[1], &data)) == 1 ||
      (data.win = bunny_start(_WIN_X, _WIN_Y, false, "Raytracer 2"))
       == NULL ||
       (data.pix = bunny_new_pixelarray(_AAWIN_Y, _AAWIN_X)) == NULL ||
      (data.actual = bunny_new_pixelarray(_WIN_Y, _WIN_X)) == NULL)
    return (print_error("Inilisation failed\n"));
  if (ac >= 4 && av[3][0] == 'o')
    {
      if (load_obj(av[2], &data.tri) == -1)
	return (1);
      data.mode = 0;
    }
  else if (ac >= 3 && (data.save = bunny_strdup(av[2])) == NULL)
    return (1);
  data.on_off = 0;
  bunny_set_loop_main_function(mainloop);
  bunny_set_key_response(exit_esc);
  bunny_loop(data.win, 150, &data);
  bunny_stop(data.win);
  free_ray(&data);
  return (0);
}
