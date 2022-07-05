/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_matrix.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 10:28:16 by ldelmas           #+#    #+#             */
/*   Updated: 2021/04/12 16:25:40 by ldelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include "../includes/calc.h"

double	**set_matrix(t_2dvec dim)
{
	double	**matrix;
	double	*elements;
	int		i;

	matrix = malloc(dim.x * sizeof(*matrix));
	elements = malloc(dim.y * dim.x * sizeof(**matrix));
	if (!matrix || !elements)
	{
		free(matrix);
		free(elements);
		return ((void *)0);
	}
	i = -1;
	while (++i < dim.x)
		matrix[i] = elements + (i * dim.y);
	return (matrix);
}

double	**set_idmatrix(t_2dvec dim)
{
	double	**matrix;
	int		i;
	int		j;

	matrix = set_matrix(dim);
	if (!matrix)
		return ((void *)0);
	i = -1;
	while (++i < dim.x)
	{
		j = -1;
		while (++j < dim.y)
		{
			if (j == i)
				matrix[i][j] = 1;
			else
				matrix[i][j] = 0;
		}
	}
	return (matrix);
}

double	**set_transmatrix(double xaxis[3], double yaxis[3],
			double zaxis[3], double pos[3])
{
	double		**transmatrix;
	double		*elements;
	int			i;

	transmatrix = malloc(4 * sizeof(double *));
	elements = malloc(16 * sizeof(double));
	if (!xaxis || !yaxis || !zaxis || !pos || !transmatrix || !elements)
	{
		free(transmatrix);
		free(elements);
		return ((void *)0);
	}
	i = -1;
	while (++i < 4)
		transmatrix[i] = elements + (i * 4);
	while (--i > -1)
	{
		transmatrix[0][i] = xaxis[i];
		transmatrix[1][i] = yaxis[i];
		transmatrix[2][i] = zaxis[i];
		transmatrix[3][i] = pos[i];
		transmatrix[i][3] = 0;
	}
	transmatrix[3][3] = 1;
	return (transmatrix);
}
