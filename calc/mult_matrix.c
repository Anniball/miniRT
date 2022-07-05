/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mult_matrix.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 11:59:38 by ldelmas           #+#    #+#             */
/*   Updated: 2021/04/12 16:17:16 by ldelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include "../includes/calc.h"

static double	sum_matrix(double **mat1, double **mat2, int lim, t_2dvec pos)
{
	int		i;
	double	sum;

	sum = 0;
	i = -1;
	while (++i < lim)
		sum += (mat1[pos.x][i] * mat2[i][pos.y]);
	return (sum);
}

double	**matrix_product(t_2dvec dim1, t_2dvec dim2,
		double **mat1, double **mat2)
{
	int		i;
	int		j;
	double	**matrix;
	double	*elements;

	if (dim1.y != dim2.x || !mat1 || !mat2 || !(*mat1) || !(*mat2)
		|| !(matrix = malloc(sizeof(*matrix) * dim1.x))
		|| !(elements = malloc(sizeof(**matrix) * dim1.x * dim2.y)))
		return ((void *)0);
	i = -1;
	while (++i < dim1.x)
		matrix[i] = elements + (i * dim2.y);
	i = -1;
	while (++i < dim1.x)
	{
		j = -1;
		while (++j < dim2.y)
			matrix[i][j] = sum_matrix(mat1, mat2, dim1.y, set_2dvec(i, j));
	}
	return (matrix);
}
