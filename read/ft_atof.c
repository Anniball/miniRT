/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 12:01:44 by ldelmas           #+#    #+#             */
/*   Updated: 2021/04/12 13:32:41 by ldelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/read.h"
#include <stdio.h>

static double	get_dec(const char *str)
{
	double	value;
	double	dec;
	int		i;

	value = 0;
	dec = 0.1;
	i = 0;
	while (ft_isdigit(str[i]))
	{
		value = value + (dec * (float)(str[i++] - '0'));
		dec *= 0.1;
	}
	return (value);
}

double	ft_atof(const char *str)
{
	int					i;
	double				value;
	int					sign;

	value = 0;
	sign = 1;
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (ft_isdigit(str[i]))
		value = (value * 10) + (str[i++] - '0');
	if (str[i] == '.')
		value = value + get_dec(str + i + 1);
	value = (float)sign * value;
	return (value);
}
