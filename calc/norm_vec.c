/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm_vec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 17:31:04 by ldelmas           #+#    #+#             */
/*   Updated: 2021/04/12 16:18:30 by ldelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/calc.h"
#include <math.h>

t_2dfvec	norm_2df(t_2dfvec vctr)
{
	double		base;
	t_2dfvec	abs;

	abs = set_2dfvec(fabs(vctr.x), fabs(vctr.y));
	if (abs.x >= abs.y)
		base = abs.x;
	else
		base = abs.y;
	vctr = set_2dfvec(vctr.x / base, vctr.y / base);
	return (vctr);
}

t_3dfvec	normalize_ray(t_3dfvec vctr)
{
	float	len;

	len = sqrt((vctr.x * vctr.x) + (vctr.y * vctr.y) + (vctr.z * vctr.z));
	if (len)
		return (set_3dfvec(vctr.x / len, vctr.y / len, vctr.z / len));
	return (vctr);
}
