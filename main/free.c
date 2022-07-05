/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 10:18:04 by ldelmas           #+#    #+#             */
/*   Updated: 2021/04/19 15:43:12 by ldelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../includes/geom.h"
#include "../includes/read.h"

static void	free_mat(t_material *mat)
{
	free(mat->txtr_name);
	free(mat->bump_name);
	free(mat->nrml_name);
	free(mat);
}

void	free_solid(t_solid *obj)
{
	int	i;

	free(*(obj->trans));
	free(obj->trans);
	if (obj->mat)
		free_mat(obj->mat);
	if (obj->points)
	{
		i = -1;
		while (obj->points[++i])
			free(obj->points[i]);
		free(obj->points);
	}
	if (obj->sides)
		free(obj->sides);
	free(obj);
}

void	free_objects(t_solid *objs, t_light *lights, t_camera *cam)
{
	t_solid		*tmp;
	t_light		*tmp_l;
	t_camera	*tmp_c;

	printf("Freeing objects.\n");
	while (objs)
	{
		tmp = objs;
		objs = objs->next;
		free_solid(tmp);
	}
	while (lights)
	{
		tmp_l = lights;
		lights = lights->next;
		free(tmp_l);
	}
	while (cam)
	{
		tmp_c = cam;
		cam = cam->next;
		free(tmp_c->orientation);
		free(tmp_c->position);
		free(tmp_c);
	}
}
