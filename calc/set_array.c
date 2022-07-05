/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_array.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 09:42:57 by ldelmas           #+#    #+#             */
/*   Updated: 2021/04/12 16:19:56 by ldelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/calc.h"
#include <math.h>
#include <stdlib.h>

double	*set_4dfarray(double x, double y, double z, double h)
{
	double	*arr;

	arr = malloc(sizeof(arr) * 4);
	if (!arr)
		return ((void *)0);
	arr[0] = x;
	arr[1] = y;
	arr[2] = z;
	arr[3] = h;
	return (arr);
}

double	*set_3dfarray(double x, double y, double z)
{
	double	*arr;

	arr = malloc(sizeof(arr) * 3);
	if (!arr)
		return ((void *)0);
	arr[0] = x;
	arr[1] = y;
	arr[2] = z;
	return (arr);
}
