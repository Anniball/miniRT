/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   length_vec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 15:15:59 by ldelmas           #+#    #+#             */
/*   Updated: 2021/02/11 16:13:25 by ldelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/calc.h"
#include <math.h>

double	length_3dfvec(t_3dfvec vctr)
{
	return (sqrt((vctr.x * vctr.x) + (vctr.y * vctr.y) + (vctr.z * vctr.z)));
}
