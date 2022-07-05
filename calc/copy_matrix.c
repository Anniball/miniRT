/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_matrix.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 11:12:26 by ldelmas           #+#    #+#             */
/*   Updated: 2021/02/11 16:12:37 by ldelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/calc.h"
#include <math.h>
#include <stdlib.h>

double	**copy_matrix(t_2dvec dim, double **matrix)
{
	double	**cpy;
	int		i;
	int		j;

	cpy = set_matrix(dim);
	i = -1;
	while (++i < dim.x)
	{
		j = -1;
		while (++j < dim.y)
			cpy[i][j] = matrix[i][j];
	}
	return (cpy);
}
