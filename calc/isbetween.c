/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isbetween.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 17:33:12 by ldelmas           #+#    #+#             */
/*   Updated: 2021/04/12 16:16:37 by ldelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/calc.h"
#include <math.h>

int	isbetween(double min, double max, double val)
{
	double	tmp;

	if (min > max)
	{
		tmp = min;
		min = max;
		max = tmp;
	}
	if (val > min && val < max)
		return (1);
	return (0);
}
