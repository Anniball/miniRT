/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vecadd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 11:08:40 by ldelmas           #+#    #+#             */
/*   Updated: 2021/04/12 16:26:23 by ldelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/calc.h"
#include <math.h>

t_3dfvec	vecadd_3dfvec(t_3dfvec u, t_3dfvec v)
{
	t_3dfvec	vec;

	vec.x = u.x + v.x;
	vec.y = u.y + v.y;
	vec.z = u.z + v.z;
	return (vec);
}
