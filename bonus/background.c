/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 14:30:19 by ldelmas           #+#    #+#             */
/*   Updated: 2021/04/13 13:38:15 by ldelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <math.h>
#include "../includes/geom.h"
#include "../includes/read.h"
#include "../includes/main.h"
#include "../includes/bonus.h"

int	get_background_pixel(t_2dvec pos, t_2dvec screen, t_data background)
{
	t_2dvec	b_pos;
	int		max;

	if (!background.img)
		return (0x00100020);
	if (screen.x >= screen.y)
		max = screen.x;
	else
		max = screen.y;
	b_pos.x = (int)(((double)pos.x / max) * W_SKY);
	b_pos.y = (int)(((double)pos.y / max) * H_SKY);
	return (pixel_get(&background, b_pos.y, b_pos.x));
}
