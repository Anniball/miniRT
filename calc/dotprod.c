/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dotprod_vec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 15:59:42 by ldelmas           #+#    #+#             */
/*   Updated: 2021/02/11 16:13:43 by ldelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/calc.h"
#include <math.h>

double	dotprod_3dfvec(t_3dfvec a, t_3dfvec b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}
