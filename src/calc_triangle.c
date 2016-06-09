/*
** calc_triangle.c for  in /home/puente_t/rendu/Info/gfx_raytracer2
**
** Made by Timothée Puentes
** Login   <puente_t@epitech.net>
**
** Started on  Mon May  9 18:07:06 2016 Timothée Puentes
** Last update Thu May 19 13:49:10 2016 Timothée Puentes
*/

#include <math.h>
#include <lapin.h>
#include "raytracer1.h"

static void	get_t_trian(t_trian *trian, t_triangle obj, unsigned int i)
{
  trian->vec[0] = obj.vertices[obj.face[i].f - 1];
  trian->vec[1] = obj.vertices[obj.face[i].s - 1];
  trian->vec[2] = obj.vertices[obj.face[i].t - 1];
  trian->norm = obj.vnorm[i];
}

static double	get_lenght(t_3d_pos vec)
{
  double	res;

  res = vec.x * vec.x + vec.y * vec.y + vec.z * vec.z;
  return (sqrt(res));
}

static void	get_angle(double *angle, t_obj *obj, t_3d_pos *hit)
{
  double	ab_ac;

  ab_ac = get_deg(translate_vec3d(obj->trian.vec[2], obj->trian.vec[0]),
		  translate_vec3d(obj->trian.vec[1], obj->trian.vec[0]));
  angle[0] = get_deg(translate_vec3d(*hit, obj->trian.vec[0]),
		     translate_vec3d(obj->trian.vec[2], obj->trian.vec[0]));
  angle[1] = ab_ac - angle[0];
  angle[2] = M_PI - angle[0] - angle[1];
}

static void	alpha_trian(t_obj *obj, t_3d_pos *ray,
			    t_inter *inter)
{
  t_3d_pos	hit;
  double	demon;
  double	sin_val;
  double	u;
  double	v;
  double	alpha;
  t_mat		mat;
  double	angle[3];

  if (my_abs(demon = dot(TRINORM, DIR)) < MIN)
    return ;
  alpha = dot(translate_vec3d(obj->trian.vec[0], ORI), TRINORM) / demon;
  hit = find_hit(alpha, &ray[0], &ray[1]);
  get_angle(angle, obj, &hit);
  sin_val = GET_LEN(hit, obj->trian.vec[0]) / sin(angle[2]);
  u = sin(angle[1]) * sin_val /
    GET_LEN(obj->trian.vec[1], obj->trian.vec[0]);
  v = sin(angle[0]) * sin_val /
    GET_LEN(obj->trian.vec[2], obj->trian.vec[0]);
  if (u < 0 || v < 0 || u + v > 1)
    return ;
  mat = obj->trian.mat;
  if (alpha > 0 && (alpha < inter->alpha || inter->alpha < 0))
    *inter = set_inter(alpha, mat, TRINORM);
}

void		ray_color_tri(t_bunny_pixelarray *pix,
			      t_data *data,
			      t_3d_pos *ray,
			      t_bunny_position *pos)
{
  unsigned int	i;
  double	diffuse;
  t_trian	trian;
  t_inter	inter;

  inter = init_inter();
  i = -1;
  while (++i < data->tri.nb_face)
    {
      get_t_trian(&trian, data->tri, i);
      alpha_trian((t_obj *)&trian, ray, &inter);
    }
  if (inter.alpha > 0)
    {
      inter.mat.color.full = WHITE;
      diffuse = get_cos_a(&ray[0], &inter.normal);
      inter.mat.color.argb[0] *= diffuse;
      inter.mat.color.argb[1] *= diffuse;
      inter.mat.color.argb[2] *= diffuse;
    }
  tekpixel(pix, pos, &inter.mat.color);
}
