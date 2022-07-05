/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_mat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 11:35:45 by ldelmas           #+#    #+#             */
/*   Updated: 2022/07/05 12:58:32 by ldelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <math.h>
#include <stdlib.h>
#include "../includes/calc.h"
#include "../includes/geom.h"
#include "../includes/mlx_utils.h"
#include "../includes/read.h"
#include "../includes/main.h"
#include "../includes/bonus.h"
#include <stdio.h>

t_material	*check_mat(char **str)
{
	int			*col;
	char		type;
	t_material	*mat;

	col = (void *)0;
	type = '\0';
	while (ft_isspace(**str))
		(*str)++;
	if (ft_isdigit(**str))
		col = get_col(str);
	else
		return (bonus_mat(str));
	if (((ft_isdigit(**str)) && !col))
	{
		ft_putstr_fd(2, "Error\nValue should be an integer or bonus char.\n");
		free(col);
		return ((void *)0);
	}
	(*str)++;
	mat = set_material(*col, SPEC, N, type);
	free(col);
	return (mat);
}
