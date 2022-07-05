/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 12:01:15 by ldelmas           #+#    #+#             */
/*   Updated: 2021/04/13 11:19:30 by ldelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/calc.h"
#include "../includes/geom.h"
#include "../includes/mlx_utils.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

t_material	*set_material(int color, double n, double ks, char c)
{
	t_material	*mat;

	mat = malloc(sizeof(t_material));
	if (!mat)
		return ((void *)0);
	mat->color = color;
	mat->n = n;
	mat->ks = ks;
	mat->type = c;
	mat->txtr_name = (void *)0;
	mat->nrml_name = (void *)0;
	mat->bump_name = (void *)0;
	mat->texture.img = (void *)0;
	mat->bump.img = (void *)0;
	mat->normal.img = (void *)0;
	return (mat);
}
