/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_interval.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 10:03:06 by ldelmas           #+#    #+#             */
/*   Updated: 2021/04/20 11:12:59 by ldelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/calc.h"
#include "../includes/read.h"
#include <math.h>

int	interval_3dfvec(t_3dfvec rot, double min, double max)
{
	if (rot.x <= max && rot.x >= min
		&& rot.y <= max && rot.y >= min
		&& rot.z <= max && rot.z >= min)
		return (1);
	ft_putstr_fd(2, "Error\nWrong interval in one of the values.\n");
	return (0);
}
