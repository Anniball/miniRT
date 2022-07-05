/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_vals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 12:53:04 by ldelmas           #+#    #+#             */
/*   Updated: 2021/04/14 12:33:05 by ldelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/read.h"
#include "../includes/calc.h"
#include "../includes/geom.h"
#include <stdio.h>

static t_3dfvec	*putret(int fd, const char *str, t_3dfvec *ret)
{
	ft_putstr_fd(fd, (char *)(str));
	free(ret);
	return ((void *)0);
}

static void	pass_float(char **str)
{
	if (**str == '-' || **str == '+')
		(*str)++;
	while (ft_isdigit(**str))
		(*str)++;
	if (**str == '.')
	{
		(*str)++;
		while (ft_isdigit(**str))
			(*str)++;
	}
}

t_3dfvec	*get_fvals(char **str)
{
	double		vals[3];
	int			count;
	t_3dfvec	*vec;

	vec = malloc(sizeof(*vec));
	if (!vec)
		return ((void *)0);
	while (ft_isspace(**str))
		(*str)++;
	if (!(ft_isdigit(**str)) && **str != '-' && **str != '+')
		return (putret(2, "Error\nValue should be an integer.\n", vec));
	count = 0;
	while (count++ < 3)
	{
		vals[count - 1] = ft_atof(*str);
		pass_float(str);
		if (**str == ',')
			(*str)++;
		else
			break ;
	}
	if (count != 3)
		return (putret(2, "Error\nWrong number of values.\n", vec));
	*vec = (set_3dfvec(vals[0], vals[1], vals[2]));
	return (vec);
}

double	get_fval(char **str)
{
	double	val;

	while (ft_isspace(**str))
		(*str)++;
	if (!(ft_isdigit(**str)))
	{
		ft_putstr_fd(2, "Wrong type of value. Should be an integer.\n");
		return (-1.0);
	}
	val = ft_atof(*str);
	pass_float(str);
	return (val);
}

int	get_val(char **str)
{
	int	val;

	while (ft_isspace(**str))
		(*str)++;
	if (!(ft_isdigit(**str)))
	{
		ft_putstr_fd(2, "Wrong type of value. Should be an integer.\n");
		return (-1);
	}
	val = ft_atoi(*str);
	while (ft_isdigit(**str))
		(*str)++;
	return (val);
}
