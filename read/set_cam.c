/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cam.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 11:56:42 by ldelmas           #+#    #+#             */
/*   Updated: 2021/04/21 11:02:09 by ldelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/read.h"
#include "../includes/calc.h"
#include "../includes/geom.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

static t_camera	*free_cam(t_camera *cam)
{
	free(cam->orientation);
	free(cam->position);
	free(cam);
	return ((void *)0);
}

t_camera	*set_cam(char *line, t_camera *next)
{
	t_camera	*cam;
	float		fov;

	cam = malloc(sizeof(*cam));
	if (!cam)
		return ((void *)0);
	line += 1;
	cam->position = get_fvals(&line);
	cam->orientation = get_fvals(&line);
	fov = get_fval(&line);
	if (cam->orientation && cam->position && fov > 0 && *line == '\0'
		&& !(cam->orientation->x == 0 && cam->orientation->y == 0
			&& cam->orientation->z == 0)
		&& interval_3dfvec(*cam->orientation, -1, 1))
	{
		cam->fov = fov;
		cam->next = next;
		*(cam->orientation) = normalize_ray(*(cam->orientation));
	}
	else
		cam = free_cam(cam);
	return (cam);
}
