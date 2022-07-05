/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_matrix.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 13:58:31 by ldelmas           #+#    #+#             */
/*   Updated: 2021/04/12 16:18:52 by ldelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include "../includes/calc.h"
#include <stdio.h>

void	print_matrix(t_2dvec dim, double **mtrx)
{
	int	i;
	int	j;

	if (!mtrx)
		return ;
	i = -1;
	while (++i < dim.x)
	{
		j = -1;
		while (++j < dim.y)
		{
			printf("%+-8.3f", mtrx[i][j]);
		}
		printf("\n");
	}
}
