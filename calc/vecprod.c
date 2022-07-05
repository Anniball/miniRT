/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vecprod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 13:21:28 by ldelmas           #+#    #+#             */
/*   Updated: 2021/04/12 16:28:46 by ldelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/calc.h"
#include <math.h>

t_3dfvec	vecprod_3dfvec(t_3dfvec u, t_3dfvec v)
{
	t_3dfvec	vec;

	vec.x = (u.y * v.z) - (u.z * v.y);
	vec.y = (u.z * v.x) - (u.x * v.z);
	vec.z = (u.x * v.y) - (u.y * v.x);
	return (vec);
}
