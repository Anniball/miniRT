/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scalprod.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 11:10:04 by ldelmas           #+#    #+#             */
/*   Updated: 2021/04/12 16:19:00 by ldelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/calc.h"
#include <math.h>

t_3dfvec	scalprod_3dfvec(t_3dfvec u, double f)
{
	t_3dfvec	vec;

	vec.x = u.x * f;
	vec.y = u.y * f;
	vec.z = u.z * f;
	return (vec);
}
