/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 10:49:14 by ldelmas           #+#    #+#             */
/*   Updated: 2022/07/05 12:56:33 by ldelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <math.h>
#include "../includes/geom.h"
#include "../includes/read.h"
#include "../includes/main.h"
#include "../includes/bonus.h"

static int	**send_camera_rays(t_2dvec screen, t_param *par, int **image,
															t_camera *cam)
{
	t_2dvec		s;
	t_opti		o;

	printf("Setting pixels for a camera angle.\n");
	o.ratio = (double)screen.x / screen.y;
	o.trig_fov = fabs(tan(cam->fov / 2));
	o = set_local_cam(o, cam);
	s.x = -1;
	while (++(s.x) < screen.y)
	{
		s.y = -1;
		while (++(s.y) < screen.x)
		{
			o.s = set_2dfvec((double)s.x + 0.5, (double)s.y + 0.5);
			if (par->aa <= 1)
				image[s.y][s.x] = get_pixel_color(screen, par, o,
						get_background_pixel(s, screen, par->skybox));
			else if (par->aa > 1)
				image[s.y][s.x] = set_aa(screen, par, o);
			if (par->filter == 's')
				image[s.y][s.x] = sepia_filter(image[s.y][s.x]);
		}
	}
	return (image);
}

static int	**no_camera(t_2dvec screen, int **image)
{
	t_2dvec	count;

	printf("Black screen becaus of no camera.\n");
	count.x = -1;
	while (++count.x < screen.y)
	{
		count.y = -1;
		while (++count.y < screen.x)
			image[count.y][count.x] = 0;
	}
	return (image);
}

int	***translate_objects(t_param *param, t_2dvec size, int ***images)
{
	t_camera	*tmp_c;
	int			i;

	if (!(param->cams))
		*images = no_camera(size, *images);
	else
	{
		i = -1;
		tmp_c = param->cams;
		while (images[++i])
		{
			if (param->mult == 1)
				images[i] = multi_ray(size, param, images[i], tmp_c);
			else
				images[i] = send_camera_rays(size, param, images[i], tmp_c);
			param->cams = tmp_c->next;
			free(tmp_c->orientation);
			free(tmp_c->position);
			free(tmp_c);
			tmp_c = param->cams;
		}
	}
	free_objects(param->objs, param->lights, (void *)0);
	free(param);
	return (images);
}
