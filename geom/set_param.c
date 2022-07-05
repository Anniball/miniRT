/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_param.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 15:32:46 by ldelmas           #+#    #+#             */
/*   Updated: 2021/04/13 11:46:16 by ldelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/geom.h"
#include "../includes/calc.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

static void	free_matrixes(double ***matrixes)
{
	int		i;

	i = -1;
	while (++i < 3)
	{
		free(matrixes[0][i]);
		free(matrixes[1][i]);
		free(matrixes[2][i]);
	}
	free(matrixes[0]);
	free(matrixes[1]);
	free(matrixes[2]);
	free(matrixes);
}

static double	***malloc_rows(void)
{
	double		***matrixes;

	matrixes = malloc(sizeof(*matrixes) * 3);
	if (!matrixes)
		return ((void *)0);
	matrixes[0] = malloc(sizeof(*matrixes[0]) * 3);
	matrixes[1] = malloc(sizeof(*matrixes[1]) * 3);
	matrixes[2] = malloc(sizeof(*matrixes[2]) * 3);
	if (!matrixes[0] || !matrixes[1] || !matrixes[2])
	{
		free(matrixes[0]);
		free(matrixes[1]);
		free(matrixes[2]);
		return ((void *)0);
	}
	return (matrixes);
}

double	**set_rot(double xangle, double yangle, double zangle)
{
	double		***matrixes;
	double		**rot1;
	double		**rot2;
	t_2dvec		size;

	matrixes = malloc_rows();
	if (!matrixes)
		return ((void *)0);
	size = set_2dvec(3, 3);
	matrixes[0][0] = set_3dfarray(1, 0, 0);
	matrixes[0][1] = set_3dfarray(0, cos(xangle), -sin(xangle));
	matrixes[0][2] = set_3dfarray(0, sin(xangle), cos(xangle));
	matrixes[1][0] = set_3dfarray(cos(yangle), 0, sin(yangle));
	matrixes[1][1] = set_3dfarray(0, 1, 0);
	matrixes[1][2] = set_3dfarray(-sin(yangle), 0, cos(yangle));
	matrixes[2][0] = set_3dfarray(cos(zangle), -sin(zangle), 0);
	matrixes[2][1] = set_3dfarray(sin(zangle), cos(zangle), 0);
	matrixes[2][2] = set_3dfarray(0, 0, 1);
	rot1 = matrix_product(size, size, matrixes[0], matrixes[1]);
	rot2 = matrix_product(size, size, rot1, matrixes[2]);
	free_matrixes(matrixes);
	free(*rot1);
	free(rot1);
	return (rot2);
}

double	**set_scale(t_3dfvec scale)
{
	double		**matrix;
	double		xyz[3];
	int			i;
	int			j;

	matrix = set_matrix(set_2dvec(3, 3));
	if (!matrix)
		return ((void *)0);
	xyz[0] = scale.x;
	xyz[1] = scale.y;
	xyz[2] = scale.z;
	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (++j < 3)
		{
			if (i == j)
				matrix[i][j] = xyz[i];
			else
				matrix[i][j] = 0;
		}
	}
	return (matrix);
}
