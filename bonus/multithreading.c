/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multithreading.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 15:03:35 by ldelmas           #+#    #+#             */
/*   Updated: 2021/06/15 17:55:27 by ldelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <math.h>
#include <pthread.h>
#include "../includes/geom.h"
#include "../includes/read.h"
#include "../includes/mlx_utils.h"
#include "../includes/main.h"
#include "../includes/bonus.h"

static int	pixel_color_calc(t_opti o, t_thread *all, t_2dvec s)
{
	int	color;

	if ((all->par->aa > 1))
		color = set_aa(all->screen, all->par, o);
	else
		color = get_pixel_color(all->screen, all->par, o,
				get_background_pixel(s, all->screen, all->par->skybox));
	if (all->par->filter == 's')
		color = sepia_filter(color);
	return (color);
}

static void	*thread_rays(void *var)
{
	t_2dvec		s;
	t_opti		o;
	t_thread	*all;

	all = (t_thread *)var;
	o.ratio = (double)all->screen.x / all->screen.y;
	o.trig_fov = tan(all->cam->fov / 2);
	o = set_local_cam(o, all->cam);
	s.x = all->num;
	while (s.x < all->screen.y)
	{
		s.y = -1;
		while (++(s.y) < all->screen.x)
		{
			o.s = set_2dfvec((double)s.x + 0.5, (double)s.y + 0.5);
			all->image[s.y][s.x] = pixel_color_calc(o, all, s);
		}
		s.x += THREADS;
	}
	return ((void *)0);
}

static t_thread	set_var(t_2dvec screen, t_param *par,
						int **image, t_camera *cam)
{
	t_thread	all;

	all.screen = screen;
	all.par = par;
	all.image = image;
	all.cam = cam;
	return (all);
}

int	**multi_ray(t_2dvec screen, t_param *par, int **image, t_camera *cam)
{
	pthread_t	t[THREADS];
	t_thread	all[THREADS];
	int			i;

	printf("Setting pixels in multithreading for a camera angle.\n");
	i = -1;
	while (++i < THREADS)
	{
		all[i] = set_var(screen, par, image, cam);
		all[i].num = i;
		pthread_create(t + i, (void *)0, thread_rays, (void *)(all + i));
	}
	i = -1;
	while (++i < THREADS)
		pthread_join(t[i], (void *)0);
	return (image);
}
