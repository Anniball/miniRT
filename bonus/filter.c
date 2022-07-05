/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 17:10:31 by ldelmas           #+#    #+#             */
/*   Updated: 2021/04/21 15:24:22 by ldelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mlx_utils.h"

int	monochromatic_filter(int color)
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	unsigned char	av;

	r = get_r(&color);
	g = get_g(&color);
	b = get_b(&color);
	av = (unsigned char)((int)(r + g + b) / 3);
	return (create_argb(0, av, av, av));
}

int	sepia_filter(int color)
{
	unsigned char	old[3];
	unsigned int	new[3];

	old[0] = get_r(&color);
	old[1] = get_g(&color);
	old[2] = get_b(&color);
	new[0] = (unsigned int)(old[0] * 0.393)
		+ (unsigned int)(old[1] * 0.769)
		+ (unsigned int)(old[2] * 0.189);
	new[1] = (unsigned int)(old[0] * 0.349)
		+ (unsigned int)(old[1] * 0.686)
		+ (unsigned int)(old[2] * 0.168);
	new[2] = (unsigned int)(old[0] * 0.272)
		+ (unsigned int)(old[1] * 0.534)
		+ (unsigned int)(old[2] * 0.131);
	if (new[0] > 255)
		new[0] = 255;
	if (new[1] > 255)
		new[1] = 255;
	if (new[2] > 255)
		new[2] = 255;
	return (create_argb(0,
			(unsigned char)new[0],
			(unsigned char)new[1],
			(unsigned char)new[2]));
}
