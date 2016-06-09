/*
** raytracer1.h for  in /home/puente_t/rendu/Info/gfx_raytracer1
**
** Made by Timothée Puentes
** Login   <puente_t@epitech.net>
**
** Started on  Tue Feb  2 16:39:02 2016 Timothée Puentes
** Last update Sun May 22 23:00:15 2016 Timothée Puentes
*/

#ifndef RAYTRACER1_H_
# define RAYTRACER1_H_

# include <unistd.h>
# include <lapin.h>
# include <stdio.h>
# include <pthread.h>
# include <stddef.h>

# define MIN	0.0001
# define OPEN_F ("Open failed.\n")
# define MALLOC_F ("Malloc failed.\n")
# define W_NUM ("Bad number.\n")
# define W_VERTC ("Unknown vertices.\n")
# define W_NORM_FACE ("Face's numbers and norm's numbers are not equal.\n")

# define		AA_SAMPLE 2
# define		IS_N(c) ((c >= '0' && c <= '9') ? (1) : (0))

# define		KILOO 1000
# define		MEGAO KILOO * KILOO
# define		RAM 150

# define		CATX data->cat->clip_x_position
# define		CATY data->cat->clip_y_position

# define		DEF_WIN_X 1000
# define		DEF_WIN_Y 1000

# define		WIN_X data->size.x
# define		WIN_Y data->size.y
# define		AAWIN_X AA_SAMPLE * WIN_X
# define		AAWIN_Y AA_SAMPLE * WIN_Y

# define		_WIN_X data.size.x
# define		_WIN_Y data.size.y
# define		_AAWIN_X AA_SAMPLE * _WIN_X
# define		_AAWIN_Y AA_SAMPLE * _WIN_Y

# define		PIX_W pix->clipable.clip_width
# define		PIX_H pix->clipable.clip_height

# define		NBOBJ data->nb_obj
# define		NBLIG data->nb_light
# define		DEG_TO_RAD  2 * M_PI / (double)360
# define		DIFFUSE light.diffuse
# define		SPECULAR light.specular
# define		PLAN 0
# define		SPHERE 1
# define		CYLINDER 2
# define		CONE 3
# define		CUBE 4

# define		TYPE (int)(data->obj[i].plan.type)
# define		DIR ray[0]
# define		ORI ray[1]
# define		CX obj->sphe.pos.x
# define		CY obj->sphe.pos.y
# define		CZ obj->sphe.pos.z
# define		RAD obj->sphe.rad
# define		PATH data->obj[idx].sphe.path
# define		TEXTURE data->obj[idx].sphe.texture
# define		HEIGTH obj->sphe.texture->clipable.clip_height
# define		WIDTH obj->sphe.texture->clipable.clip_width
# define		COLOR_F obj->sphe.mat.color.full

# define		P_PATH data->obj[idx].plan.path
# define		P_TEXTURE data->obj[idx].plan.texture

# define		GET_LEN(c, d) get_lenght(translate_vec3d(c, d))
# define		VEC_T obj->trian.vec
# define		CXX obj->cone.pos.x
# define		CXY obj->cone.pos.y
# define		CXZ obj->cone.pos.z
# define		RADX obj->cone.rad
# define		OPEN obj->cone.open

# define		CROT obj->cyli.rot
# define		CPOS obj->cyli.pos
# define		NORMAL_CYL(c) get_normale_cyl(nray, alpha[c], \
						      &CROT, &pos)
# define		TRINORM obj->trian.norm
# define		OROT obj->cone.rot
# define		OPOS obj->cone.pos
# define		OSIZ obj->cone.size
# define		NORMAL_CAP get_normale_cap(&cyli->rot)
# define		NORMAL_OCAP get_normale_cap(&obj->cone.rot)
# define		NORMAL_PCAP get_normale_cap(&obj->plan.rot)
# define		NORMAL_CON(c) get_normale_cone(nray, alpha[c] \
						       , &OROT, &pos)
# define		ABS(c) ((c < 0) ? (-c) : (c))
# define		L_NORM inter->normal
# define		NORMS(c) get_normal_s(alpha[c], &obj->sphe.pos, ray)
# define		SECONDARY data->obj[idx].plan.mat.color_bis.full
# define		REFLET(nb) ncolor->argb[nb] * inter->mat.reflect
# define		OLD_REFLEC(nb) color->argb[nb] * \
  (1 - inter->mat.reflect)

# define		GET_DIF ((tmp.diffuse < 0) ? (0) : (tmp.diffuse))
# define		LIGHT data->light
# define		LIG_OR_OBJ ((fdf_strcmp(name, "Light")) ? (&c) : (&x))
# define		TMP data->tmp

# define		PERLIN_NOISE 255 * 2
# define		G0 perm[pos.x + perm[pos.y]] % 8
# define		G1 perm[pos.x + 1 + perm[pos.y]] % 8
# define		G2 perm[pos.x + perm[pos.y + 1]] % 8
# define		G3 perm[pos.x + 1 + perm[pos.y + 1]] % 8
# define		TMP_X (x - pos.x)
# define		TMP_Y (y - pos.y)
# define		S gradient2[G0][0] * (x - pos.x) +	\
  gradient2[G0][1] * (y - pos.y)
# define		T gradient2[G1][0] * (x - pos.x - 1) +	\
gradient2[G1][1] * (y - pos.y)
# define 		U gradient2[G2][0] * (x - pos.x) +	\
  gradient2[G2][1] * (y - pos.y - 1)
# define		V gradient2[G3][0] * (x - pos.x - 1) + \
  gradient2[G3][1] * (y - pos.y - 1)
# define		NB_THREAD 4
# define		INTENSITY data->light[inter->rank].mat.shade

typedef struct		s_3d_pos
{
  double		x;
  double		y;
  double		z;
}			t_3d_pos;

typedef struct		s_mat
{
  t_color		color;
  t_color		color_bis;
  double		shine;
  double		shade;
  double		reflect;
  double		transpar;
  double		density;
}			t_mat;

typedef struct		s_inter
{
  double		alpha;
  t_mat			mat;
  t_3d_pos		normal;
  int			rank;
  int			recur;
}			t_inter;

typedef struct		s_face
{
  unsigned int		f;
  unsigned int		s;
  unsigned int		t;
}			t_face;

typedef struct		s_triangle
{
  unsigned int		nb_vertices;
  unsigned int		nb_vnorm;
  unsigned int		nb_face;
  t_3d_pos		*vertices;
  t_3d_pos		*vnorm;
  t_face		*face;
}			t_triangle;

typedef struct		s_fctn
{
  char			*s;
  int			(*fct)(t_triangle *tri, char **tab);
}			t_fctn;

typedef struct		s_sphere
{
  char			type;
  t_3d_pos		pos;
  int			rad;
  t_mat			mat;
  int			x_repeat;
  int			y_repeat;
  char			*path;
  t_bunny_pixelarray	*texture;
}			t_sphere;

typedef struct		s_plan
{
  char			type;
  t_3d_pos		rot;
  t_3d_pos		pos;
  int			norm;
  t_mat			mat;
  char			*path;
  t_bunny_pixelarray	*texture;
}			t_plan;

typedef struct		s_cylinder
{
  char			type;
  t_3d_pos		pos;
  int			rad;
  double		size;
  t_3d_pos		rot;
  t_mat			mat;
}			t_cylinder;

typedef struct		s_cube
{
  char			type;
  t_3d_pos		pos;
  double		size;
  t_3d_pos		rot;
  t_mat			mat;
}			t_cube;

typedef struct		s_bitheader
{
  char			type[2];
  int			size;
  int			empty;
  int			offset;
  int			size_head;
  int			width;
  int			height;
  short			nb_bit;
  short			byte_pix;
  int			compress;
  int			bytesize;
  int			ppi_y;
  int			ppi_x;
  int			palette_size;
  int			imp_color;
}			__attribute__((packed)) t_bitheader;

typedef struct		s_ini
{
  t_bunny_position	p;
  unsigned char		arg[4];
  unsigned int		c;
  t_color		act;
  unsigned int		*buff;
}			t_ini;

typedef struct		s_cone
{
  char			type;
  t_3d_pos		pos;
  double		size;
  double		open;
  t_3d_pos		rot;
  t_mat			mat;
}			t_cone;

typedef struct		s_trian
{
  t_3d_pos		vec[3];
  t_3d_pos		norm;
  t_mat			mat;
}			t_trian;

typedef union		u_obj
{
  t_trian		trian;
  t_cone		cone;
  t_cylinder		cyli;
  t_plan		plan;
  t_sphere		sphe;
  t_cube		cube;
}			t_obj;

typedef struct		s_light
{
  t_color		color;
  t_3d_pos		specular;
  double		shadow;
  double		diffuse;
  double		intensity;
  double		totalintensity;
}			t_light;

typedef struct		s_cam
{
  t_3d_pos		cam_pos;
  t_3d_pos		cam_rot;
}			t_cam;

typedef struct		s_thread
{
  pthread_t		t1;
  pthread_t		t2;
  pthread_t		t3;
  pthread_t		t4;
  pthread_t		t5;
  pthread_t		t6;
}			t_thread;

typedef struct		s_data
{
  int			mode;
  t_bunny_window	*win;
  t_bunny_pixelarray	*pix;
  t_bunny_pixelarray	*actual;
  t_bunny_pixelarray    *black;
  t_bunny_picture	*cat;
  char			*save;
  char			on_off;
  int			nb_light;
  t_sphere		*light;
  int			tmp;
  int			nb_obj;
  t_bunny_position	size;
  t_obj			*obj;
  t_triangle		tri;
  void			(*alpha[5])(t_obj *, t_3d_pos *,
				    t_inter *);
  int			grad[16][3];
  t_thread		p;
  t_cam			cam;
}			t_data;

/*
** basic.c
*/
int	my_strlen(const char *str);
int	my_perror(char *str);
int	my_strcmp(char *s1, char *s2);
int	my_tablen(char **tab);
int	count_tri(t_triangle *tri);

/*
** load_obj.c
*/
int	load_obj(char *path, t_triangle *tri);

/*
** my_str_to_wordtab.c
*/
char	**my_str_to_wordtab(char *str, char *delim);

/*
** initial.c
*/
void	initial(t_fctn *tab_fct);
int	initial_tri(t_triangle *tri);

/*
** my_getnbrdou.c
*/
double		my_getnbrdou(char *s);
unsigned int	my_getnbr(char *s);

/*
** load_faces.c
*/
int	load_vertices(t_triangle *tri, char **tab);
int	load_vnorm(t_triangle *tri, char **tab);
int	load_faces(t_triangle *tri, char **tab);

/*
** calc_vnorm.c
*/
int	calc_vnorm(t_triangle *tri);

/*
** my_memset.c
*/
void	*my_memset(void *s, int c, size_t n);

/*
** L reste du bordel
*/

void			aa_supp(t_data *data);
void			ray_color_tri(t_bunny_pixelarray *pix,
			      t_data *data,
			      t_3d_pos *ray,
			      t_bunny_position *pos);
unsigned int		get_texture_color(t_bunny_pixelarray *pix,
					  int x,
					  int y);
int			add_translation(t_bunny_ini *file,
					const char *scope, t_3d_pos *pos);
double			get_perlin(double x, double y, double res);
void			aa_8x(t_bunny_pixelarray *pix,
			      t_bunny_pixelarray *tmp);
int			extract_light(t_bunny_ini *file, t_data *data,
				      int idx, const char *scope);
int			extract_cyli(t_bunny_ini *file, t_data *data,
				     int idx, const char *scope);
int			extract_sphere(t_bunny_ini *file, t_data *data,
				     int idx, const char *scope);
int			extract_plan(t_bunny_ini *file, t_data *data,
				     int idx, const char *scope);
int			extract_cone(t_bunny_ini *file, t_data *data,
				     int idx, const char *scope);
int			extract_cube(t_bunny_ini *file, t_data *data,
				     int idx, const char *scope);
double			get_deg(t_3d_pos vec1, t_3d_pos vec2);

int			const_atoi(const char *str);
void			tekray(const t_bunny_position *pos_on_screen,
			       t_3d_pos *ray, t_data *data);
void			tekpixel(t_bunny_pixelarray *pix,
				 t_bunny_position *pos,
				 t_color *color);
void			ray_color(t_bunny_pixelarray *pix,
				  t_data *data,
				  t_3d_pos *ray,
				  t_bunny_position *pos);

void			alpha_plan(t_obj *obj, t_3d_pos *ray,
				   t_inter *inter);
void			alpha_sphere(t_obj *obj, t_3d_pos *ray,
				     t_inter *inter);
void			alpha_cylinder(t_obj *obj, t_3d_pos *ray,
				       t_inter *inter);
void			alpha_cone(t_obj *obj, t_3d_pos *ray,
				      t_inter *inter);
void			alpha_cube(t_obj *obj, t_3d_pos *ray,
				   t_inter *inter);

unsigned int		hex_to_color(const char *s);

int			init_map(const char *filename, t_data *data);
t_inter			set_inter(double alpha, t_mat mat, t_3d_pos normale);
t_3d_pos		get_normal_s(double alpha,
				     t_3d_pos *pos,
				     t_3d_pos *ray);
t_3d_pos		*get_vector_normal(t_3d_pos *vec);
double			get_cos_a(t_3d_pos *vec1, t_3d_pos *vec2);
t_3d_pos		matrice_rot_x(t_3d_pos *pos,
				      double alpha);
t_3d_pos		matrice_rot_y(t_3d_pos *pos,
				      double alpha);
t_3d_pos		matrice_rot_z(t_3d_pos *pos,
				      double alpha);
t_3d_pos		three_matrice(t_3d_pos *ori,
				      t_3d_pos *rot);
t_3d_pos		rev_matrice(t_3d_pos *ori,
				    t_3d_pos *rot);
int			check_limits(double size, double posy, double alpha,
				     t_3d_pos *nray);
int			check_limits(double size, double posy, double alpha,
				     t_3d_pos *nray);
t_3d_pos		get_normale_cap(t_3d_pos *rot);
t_3d_pos		get_normale_cyl(t_3d_pos *nray, double alpha,
					t_3d_pos *rot, t_3d_pos *pos);
double			check_cap(t_3d_pos *nray,
				  t_3d_pos *pos,
				  double size,
				  double rad);
void			move(t_data *data);
int			extract_cam(t_bunny_ini *file, t_data *data);
int			fdf_strcmp(const char *cs, char *ns);
t_light			create_light(t_3d_pos *pos,
				     t_3d_pos *normale,
				     t_3d_pos *ray,
				     t_data *data);
void			compute_lights(t_data *data,
				       t_3d_pos *ray,
				       t_inter *inter);
t_light			compute_light(t_data *data,
				      t_3d_pos *ray,
				      t_inter *inter);
double			scalaire(t_3d_pos *vec1,
				 t_3d_pos *vec2,
				 double angle);
t_3d_pos		get_reflected(t_3d_pos *norm,
				      t_3d_pos *vec);
t_inter			init_inter();
t_3d_pos		translate_vec3d(t_3d_pos vec,
					t_3d_pos to_move);
void			*calc_1q(void *data);
void			*calc_2q(void *data);
void			*calc_3q(void *data);
void			*calc_4q(void *data);
void			*calc_5q(void *data);
void			*calc2_1q(void *data);
void			*calc2_2q(void *data);
void			*calc2_3q(void *data);
void			*calc2_4q(void *data);
void			*calc2_5q(void *data);
void			*printing(void *_data);

t_3d_pos		find_hit(double alpha, t_3d_pos *ray,
				 t_3d_pos *pos);
void			vec_rev(t_3d_pos *vec);
void			compute_color(t_color *color,
				      t_light *light);
void			*print_error_pnt(char *str);
int			print_error(char *str);
char			*bunny_dup(const char *str);
int			extract_spherebis(t_bunny_ini	*file,
					 t_data		*data,
					 int		idx,
					 const char	*scope);
void			sphere_texturing(t_obj *obj,
					 t_3d_pos *ray,
					 double alpha,
					 t_mat *mat);
int			save_bitmap(const char *file, t_data *data);
char			*bunny_strdup(const char *src);
int			extract_planter(t_bunny_ini	*file,
					t_data		*data,
					int		idx,
					const char	*scope);
void			init_vec(t_3d_pos *vec);
int			my_abs(double nb);

void			reflect_light(t_color *color,
				      t_data *data,
				      t_3d_pos *ray,
				      t_inter *inter);
void			transparent_light(t_color *color,
					  t_data *data,
					  t_3d_pos *ray,
					  t_inter *inter);
double			dot(t_3d_pos vec1, t_3d_pos vec2);
t_3d_pos		cross(t_3d_pos vec1, t_3d_pos vec2);
void			print_cat(t_data *data);
void			init_cat(t_data *data);
void			free_ray(t_data *data);

#endif /* !RAYTRACER1_H_ */
