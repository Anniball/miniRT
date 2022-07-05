/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 17:05:05 by ldelmas           #+#    #+#             */
/*   Updated: 2021/04/13 12:33:23 by ldelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS_H
# define BONUS_H

# include "main.h"

# define THREADS 16

typedef struct s_thread
{
	t_2dvec		screen;
	t_param		*par;
	int			**image;
	t_camera	*cam;
	int			num;
}				t_thread;

int				get_bonus(char *ln, t_param *par);
void			set_bonus(t_param *par);
t_material		*bonus_mat(char **str);

int				monochromatic_filter(int color);
int				sepia_filter(int color);

int				set_aa(t_2dvec screen, t_param *par, t_opti o);

int				**multi_ray(t_2dvec screen, t_param *par,
					int **image, t_camera *cam);

t_2dfvec		uv_sphere(t_3dfvec	n);
t_2dfvec		uv_triangle(t_solid obj, t_ray_prop props);
t_2dfvec		uv_quad(t_solid obj, t_ray_prop props);
t_2dfvec		uv_cylinder(t_solid obj, t_ray_prop props);

t_3dfvec		sine_normal(t_ray_prop props, t_3dfvec n);
t_3dfvec		normal_map(t_ray_prop props);
t_3dfvec		bump_map(t_ray_prop props);
int				rainbow(t_3dfvec n);
int				checker(t_ray_prop props);

int				get_background_pixel(t_2dvec pos, t_2dvec screen,
					t_data background);

int				find_texture(void *mlx_ptr, t_solid *objs, t_param *par);
int				find_txt_col(t_ray_prop props, t_data *texture);
int				transfer_txt(t_ray_prop props, t_data *texture, t_2dvec
					transfer);
int				mipmap_txt(t_ray_prop props, t_data *texture, t_2dvec transfer);

#endif
