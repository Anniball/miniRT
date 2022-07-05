/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_light.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 11:38:12 by ldelmas           #+#    #+#             */
/*   Updated: 2021/04/13 11:30:23 by ldelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/calc.h"
#include "../includes/geom.h"
#include "../includes/mlx_utils.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

t_light	*complete_light(t_light *l, int col, t_light *next)
{
	if (!l)
		return ((void *)0);
	l->color = col;
	l->next = next;
	return (l);
}

t_light	*set_light(char type, t_3dfvec vec, double intensity)
{
	t_light	*light;

	light = malloc(sizeof(*light));
	if (!light)
		return ((void *)0);
	light->type = type;
	if (type == 'd')
		light->dir = vec;
	else if (type == 'p')
		light->pos = vec;
	light->intensity = intensity;
	return (light);
}
