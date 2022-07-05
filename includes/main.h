/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 12:00:46 by ldelmas           #+#    #+#             */
/*   Updated: 2022/07/05 17:30:38 by ldelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "../includes/geom.h"
# include "../includes/read.h"
# include "../includes/mlx.h"

# define WIDTH 4096
# define HEIGHT 4096
# define W_SKY 4096
# define H_SKY 4096

# ifndef SPEC
#  define SPEC 70
# endif

# ifndef N
#  define N 0.2
# endif

typedef struct s_vars
{
	void		*mlx;
	void		*win;
	int			***images;
	int			ref;
	t_2dvec		screen;
	t_data		img;
}				t_vars;

typedef struct s_opti
{
	t_2dfvec	s;
	double		trig_fov;
	double		ratio;
	t_3dfvec	x;
	t_3dfvec	y;
	t_3dfvec	z;
}				t_opti;

void			free_solid(t_solid *obj);
void			free_objects(t_solid *objs, t_light *lights, t_camera *cam);

int				***translate_objects(t_param *parameters, t_2dvec screen_size,
					int ***images);
int				get_pixel_color(t_2dvec screen, t_param *par,
					t_opti o, int col);
t_opti			set_local_cam(t_opti o, t_camera *cam);
t_3dfvec		set_translation(t_3dfvec axis, double angle, t_3dfvec dir);

int				***get_images(t_param *parameters, t_2dvec screen_size);
void			free_images(int ***images, t_2dvec screen_size);
int				show_image(int **images, t_data img, t_2dvec screen_size);

int				key_hook(int keycode, t_vars *vars);
int				key_exit(t_vars *vars);

void			set_screen_size(t_2dvec *screen, void *mlx);

#endif
