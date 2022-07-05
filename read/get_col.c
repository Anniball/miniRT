/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_col.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 11:26:04 by ldelmas           #+#    #+#             */
/*   Updated: 2021/04/12 14:42:41 by ldelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/read.h"
#include "../includes/calc.h"
#include "../includes/geom.h"
#include <stdio.h>

static int	*putret(int fd, const char *str, int *ret)
{
	ft_putstr_fd(fd, (char *)(str));
	return (ret);
}

static int	*test_color(int *vals)
{
	t_3dfvec		fcolor;
	unsigned char	colors[3];
	int				ret;
	int				*col;

	col = malloc(sizeof(col));
	if (!col)
		return ((void *)0);
	fcolor.x = (double)(vals[0]);
	fcolor.y = (double)(vals[1]);
	fcolor.z = (double)(vals[2]);
	ret = interval_3dfvec(fcolor, 0, 255);
	if (!ret)
		return (putret(2, "Error\nColors are in a 0-255 range.\n", (void *)0));
	colors[0] = (unsigned char)(vals[0]);
	colors[1] = (unsigned char)(vals[1]);
	colors[2] = (unsigned char)(vals[2]);
	*col = create_argb(0, colors[0], colors[1], colors[2]);
	return (col);
}

int	*get_col(char **str)
{
	int				vals[3];
	int				count;

	while (ft_isspace(**str))
		(*str)++;
	if (!(ft_isdigit(**str)))
		return (putret(2, "Error\nColor is composed of ints.\n", (void *)0));
	count = 0;
	while (count < 3)
	{
		vals[count] = ft_atoi(*str);
		while (ft_isdigit(**str))
			(*str)++;
		if (**str == ',')
			(*str)++;
		else
			break ;
		count++;
	}
	count++;
	if (count != 3)
		return (putret(2, "Error\nWrong number of color values.\n", (void *)0));
	return (test_color(vals));
}
