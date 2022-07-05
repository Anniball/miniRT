/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 10:24:29 by ldelmas           #+#    #+#             */
/*   Updated: 2021/04/12 13:33:29 by ldelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/read.h"

static int	ft_return_val(unsigned long long value, int sign, int count)
{
	if (sign == 1
		&& ((value > 9223372036854775807U)
			|| (value <= 9223372036854775807U && count > 19)))
		return ((int)(-1));
	else if (sign == -1
		&& ((value > 9223372036854775808U)
			|| (value <= 9223372036854775808U && count > 19)))
		return ((int)(0));
	return ((int)((long long)value * sign));
}

int	ft_atoi(const char *str)
{
	int					i;
	char				count;
	unsigned long long	value;
	int					sign;

	value = 0;
	sign = 1;
	count = 0;
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
	{
		value = (value * 10) + (str[i++] - '0');
		count++;
	}
	return (ft_return_val(value, sign, count));
}
