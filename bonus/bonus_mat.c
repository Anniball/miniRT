/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_mat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 16:10:04 by ldelmas           #+#    #+#             */
/*   Updated: 2021/04/21 15:14:58 by ldelmas          ###   ########.fr       */
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

static int	check_xpm(char *texture_name, int i)
{
	if (!(i == 1 && texture_name[i - 1] == '0')
		&& (i < 5 || texture_name[i - 4] != '.'
			|| texture_name[i - 3] != 'x' || texture_name[i - 2] != 'p'
			|| texture_name[i - 1] != 'm'))
	{
		free(texture_name);
		ft_putstr_fd(2, "Error\nWrong format for texture name.\n");
		return (-1);
	}
	return (0);
}

static char	*check_texture(char **str)
{
	char		*texture_name;
	int			i;

	(*str)++;
	while (ft_isspace(**str))
		(*str)++;
	i = 0;
	while ((*str)[i] && !ft_isspace((*str)[i]))
		i++;
	texture_name = malloc(sizeof(*texture_name) * (i + 1));
	if (!texture_name)
		return ((void *)0);
	texture_name[i] = '\0';
	i = -1;
	while (!ft_isspace((*str)[++i]) && ((*str)[i]))
		texture_name[i] = (*str)[i];
	printf("%s\n", texture_name);
	if (check_xpm(texture_name, i) == -1)
		return ((void *)0);
	while (i--)
		(*str)++;
	return (texture_name);
}

static char	*free_nullify_str(char **str)
{
	free(*str);
	*str = (void *)0;
	return (*str);
}

static t_material	*check_textures(char **str, int *col)
{
	t_material	*mat;

	mat = set_material(*col, SPEC, N, 't');
	mat->txtr_name = check_texture(str);
	mat->nrml_name = check_texture(str);
	mat->bump_name = check_texture(str);
	if (!mat || !mat->txtr_name || !mat->nrml_name || !mat->bump_name)
	{
		free(mat);
		free(col);
		return ((void *)0);
	}
	if (mat->txtr_name[0] == '0' && !mat->txtr_name[1])
		free_nullify_str(&mat->txtr_name);
	if (mat->nrml_name[0] == '0' && !mat->nrml_name[1])
		free_nullify_str(&mat->nrml_name);
	if (mat->bump_name[0] == '0' && !mat->bump_name[1])
		free_nullify_str(&mat->bump_name);
	free(col);
	return (mat);
}

t_material	*bonus_mat(char **str)
{
	int			*col;
	char		type;
	t_material	*mat;

	col = malloc(sizeof(*col));
	if (!col)
		return ((void *)0);
	*col = 0x00FFFFFF;
	if (**str == 'n' || **str == 'c' || **str == 's')
		type = **str;
	else if (**str == 't')
		return (check_textures(str, col));
	else
	{
		ft_putstr_fd(2, "Error\nWrong bonus material.\n");
		return ((void *)0);
	}
	if (type == 's')
		*col = 0x00FFFFFF;
	if ((type == 's' || type == 'c' || type == 'n') && *(*str + 1))
		(*str)++;
	mat = set_material(*col, SPEC, N, type);
	free(col);
	return (mat);
}
