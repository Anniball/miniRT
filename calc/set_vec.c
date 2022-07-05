/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_vec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 17:25:38 by ldelmas           #+#    #+#             */
/*   Updated: 2021/04/12 16:26:05 by ldelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/calc.h"
#include <math.h>

t_4dfvec	set_4dfvec(double x, double y, double z, double h)
{
	t_4dfvec	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	vec.h = h;
	return (vec);
}

t_3dfvec	set_3dfvec(double x, double y, double z)
{
	t_3dfvec	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

t_2dfvec	set_2dfvec(double x, double y)
{
	t_2dfvec	vec;

	vec.x = x;
	vec.y = y;
	return (vec);
}

t_2dvec	set_2dvec(int x, int y)
{
	t_2dvec	vec;

	vec.x = x;
	vec.y = y;
	return (vec);
}
