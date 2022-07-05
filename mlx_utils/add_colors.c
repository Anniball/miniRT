/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_colors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 15:23:04 by ldelmas           #+#    #+#             */
/*   Updated: 2021/04/12 13:28:50 by ldelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mlx_utils.h"

int	add_color(int color, int add)
{
	unsigned char		a;
	unsigned int		r;
	unsigned int		g;
	unsigned int		b;

	a = get_a(&color);
	r = (unsigned int)((unsigned char)get_r(&color));
	r += (unsigned int)((unsigned char)get_r(&add));
	g = (unsigned int)((unsigned char)get_g(&color));
	g += (unsigned int)((unsigned char)get_g(&add));
	b = (unsigned int)((unsigned char)get_b(&color));
	b += (unsigned int)((unsigned char)get_b(&add));
	if (r > 255)
		r = 255;
	if (g > 255)
		g = 255;
	if (b > 255)
		b = 255;
	return (create_argb(a, (char)r, (char)g, (char)b));
}
