/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 15:18:33 by ldelmas           #+#    #+#             */
/*   Updated: 2021/04/21 11:58:56 by ldelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <math.h>
#include <stdlib.h>
#include "../includes/calc.h"
#include "../includes/geom.h"
#include "../includes/mlx_utils.h"
#include "../includes/read.h"
#include "../includes/main.h"
#include <stdio.h>

int	show_image(int **images, t_data img, t_2dvec screen)
{
	t_2dvec	size;

	size.x = -1;
	printf("Putting pixels on image.\n");
	while (++size.x < screen.x)
	{
		size.y = -1;
		while (++size.y < screen.y)
			pixel_put(&img, size.x, size.y, images[size.x][size.y]);
	}
	return (0);
}

void	free_images(int ***images, t_2dvec screen)
{
	int	i;
	int	j;

	j = -1;
	while (images[++j])
	{
		i = -1;
		while (++i < screen.x)
			free(images[j][i]);
		free(images[j]);
	}
	free(images);
}

static int	get_cam_numb(t_camera *cam)
{
	int	count;

	if (!cam)
		return (1);
	count = 0;
	while (cam)
	{
		count++;
		cam = cam->next;
	}
	return (count);
}

int	***get_images(t_param *parameters, t_2dvec screen)
{
	int			***images;
	int			count;
	int			i;

	count = get_cam_numb(parameters->cams);
	images = malloc(sizeof(*images) * (count + 1));
	if (!images)
		return ((void *)0);
	images[count] = (void *)0;
	while (count--)
	{
		images[count] = malloc(sizeof(**images) * screen.x);
		if (!(images[count]))
			return ((void *)0);
		i = -1;
		while (++i < screen.x)
		{
			images[count][i] = malloc(sizeof(***images) * screen.y);
			if (!(images[count][i]))
				return ((void *)0);
		}
	}
	images = translate_objects(parameters, screen, images);
	return (images);
}
