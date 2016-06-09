/*
** pthread.c for  in /home/puente_t/rendu/Info/gfx_raytracer1
**
** Made by Timothée Puentes
** Login   <puente_t@epitech.net>
**
** Started on  Mon Feb 22 16:25:02 2016 Timothée Puentes
** Last update Wed May 18 17:36:07 2016 Timothée Puentes
*/

#include <stdio.h>
#include <lapin.h>
#include "raytracer1.h"

void			*calc_1q(void *_data)
{
  t_bunny_position	pos;
  t_3d_pos		ray[2];
  t_data		*data;

  data = _data;
  pos.x = 0;
  ray[1].x = data->cam.cam_pos.x;
  ray[1].y = data->cam.cam_pos.y;
  ray[1].z = data->cam.cam_pos.z;
  while (pos.x < AAWIN_X / NB_THREAD)
    {
      pos.y = 0;
      while (pos.y < AAWIN_Y)
	{
	  if (data->on_off <= -1)
	    return (NULL);
	  tekray(&pos, ray, data);
	  ray[0] = three_matrice(&ray[0], &data->cam.cam_rot);
	  ray_color(data->pix, data, &ray[0], &pos);
	  pos.y += 1;
	}
      pos.x += 1;
    }
  data->on_off += 1;
  return (NULL);
}

void			*calc_2q(void *_data)
{
  t_bunny_position	pos;
  t_3d_pos		ray[2];
  t_data		*data;

  data = _data;
  pos.x = (AAWIN_X * 1) / NB_THREAD;
  ray[1].x = data->cam.cam_pos.x;
  ray[1].y = data->cam.cam_pos.y;
  ray[1].z = data->cam.cam_pos.z;
  while (pos.x < (AAWIN_X * 2) / NB_THREAD)
    {
      pos.y = 0;
      while (pos.y < AAWIN_Y)
	{
	  if (data->on_off <= -1)
	    return (NULL);
	  tekray(&pos, ray, data);
	  ray[0] = three_matrice(&ray[0], &data->cam.cam_rot);
	  ray_color(data->pix, data, &ray[0], &pos);
	  pos.y += 1;
	}
      pos.x += 1;
    }
  data->on_off += 1;
  return (NULL);
}

void			*calc_3q(void *_data)
{
  t_bunny_position	pos;
  t_3d_pos		ray[2];
  t_data		*data;

  data = _data;
  pos.x = (AAWIN_X * 2) / NB_THREAD;
  ray[1].x = data->cam.cam_pos.x;
  ray[1].y = data->cam.cam_pos.y;
  ray[1].z = data->cam.cam_pos.z;
  while (pos.x < (AAWIN_X * 3) / NB_THREAD)
    {
      pos.y = 0;
      while (pos.y < AAWIN_Y)
	{
	  if (data->on_off <= -1)
	    return (NULL);
	  tekray(&pos, ray, data);
	  ray[0] = three_matrice(&ray[0], &data->cam.cam_rot);
	  ray_color(data->pix, data, &ray[0], &pos);
	  pos.y += 1;
	}
      pos.x += 1;
    }
  data->on_off += 1;
  return (NULL);
}

void			*calc_4q(void *_data)
{
  t_bunny_position	pos;
  t_3d_pos		ray[2];
  t_data		*data;

  data = _data;
  pos.x = (AAWIN_X * 3) / NB_THREAD;
  ray[1].x = data->cam.cam_pos.x;
  ray[1].y = data->cam.cam_pos.y;
  ray[1].z = data->cam.cam_pos.z;
  while (pos.x < AAWIN_X)
    {
      pos.y = 0;
      while (pos.y < AAWIN_Y)
	{
	  if (data->on_off <= -1)
	    return (NULL);
	  tekray(&pos, ray, data);
	  ray[0] = three_matrice(&ray[0], &data->cam.cam_rot);
	  ray_color(data->pix, data, &ray[0], &pos);
	  pos.y += 1;
	}
      pos.x += 1;
    }
  data->on_off += 1;
  return (NULL);
}
