/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geom.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 09:47:29 by ldelmas           #+#    #+#             */
/*   Updated: 2021/04/19 14:04:58 by ldelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GEOM_H
# define GEOM_H

# include "../includes/mlx_utils.h"

typedef struct s_material
{
	int			color;
	double		n;
	double		ks;
	char		type;
	char		*txtr_name;
	t_data		texture;
	char		*nrml_name;
	t_data		normal;
	char		*bump_name;
	t_data		bump;
}				t_material;

typedef struct s_solid
{
	char		type;
	t_3dfvec	scale;
	double		**trans;
	double		**points;
	t_3dfvec	normal;
	t_3dfvec	*sides;
	t_material	*mat;
	void		*next;
}				t_solid;

typedef struct s_ray_prop
{
	t_3dfvec	pos;
	t_3dfvec	ori;
	t_3dfvec	dir;
	double		dist;
	double		ratio;
	t_3dfvec	normal;
	t_3dfvec	m_normal;
	t_solid		inters;
}				t_ray_prop;

typedef struct s_light
{
	char		type;
	t_3dfvec	pos;
	t_3dfvec	dir;
	int			color;
	double		intensity;
	double		falloff;
	void		*next;
}				t_light;

typedef struct s_quad
{
	double	**coord;
	double	*points[4];
}				t_quad;

double			**set_rot(double xangle, double yangle, double zangle);
double			**set_scale(t_3dfvec scale);
double			**set_trans(t_3dfvec pos, t_3dfvec rot, t_3dfvec scale);
double			**set_obj_to_cam(t_3dfvec pos, t_3dfvec rot,
					t_3dfvec scale, double **cam);
double			*set_point_by_ref(double posx, double posy,
					double posz, double **ref);

t_solid			*set_plane(double **trans, t_solid *next, t_material *mat);
t_ray_prop		intersect_plane(t_ray_prop props, t_3dfvec o, t_solid obj);

t_solid			*set_quad(double **trans, t_solid *next, t_material *mat);
t_ray_prop		intersect_quad(t_ray_prop props, t_3dfvec o, t_solid obj);

t_solid			*set_sphere(double **trans, t_solid *next, t_material *mat);
t_ray_prop		intersect_sphere(t_ray_prop props, t_3dfvec origin,
					t_solid obj);

t_solid			*set_triangle(double **trans, t_3dfvec *points,
					t_solid *next, t_material *mat);
t_ray_prop		intersect_tri(t_ray_prop props, t_3dfvec origin, t_solid obj);

t_solid			*set_cylinder(double **trans, t_solid *next,
					t_material *mat, t_3dfvec scale);
t_ray_prop		intersect_cylinder(t_ray_prop props, t_3dfvec origin,
					t_solid obj);

t_light			*set_light(char type, t_3dfvec vec, double intensity);
t_light			*complete_light(t_light *l, int col, t_light *next);
int				get_lights(t_ray_prop props, t_light *lights, int tcol);
int				get_lightbyf(int color, double val);
int				get_albedo(int num, int den);
int				check_specular(t_ray_prop props, t_light light,
					t_3dfvec normal, int diffuse);

t_material		*set_material(int color, double n, double ks, char c);

int				check_shadow(t_ray_prop props, t_solid *objs, t_light *lights);

t_ray_prop		do_intersect(t_ray_prop props, t_3dfvec origin, t_solid obj);
int				check_intersection(t_ray_prop props, t_solid *objs,
					t_light *lights, int background);

#endif
