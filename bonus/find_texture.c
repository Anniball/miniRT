/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 12:30:43 by ldelmas           #+#    #+#             */
/*   Updated: 2021/04/14 12:14:33 by ldelmas          ###   ########.fr       */
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

static void	set_adress(t_data *texture)
{
	texture->addr = mlx_get_data_addr(texture->img,
			&(texture->bits_per_pixel),
			&(texture->line_length),
			&(texture->endian));
}

static int	set_by_type(t_solid *objs, void *mlx_ptr)
{
	int	size[2];

	size[0] = WIDTH;
	size[1] = HEIGHT;
	objs->mat->texture.img = mlx_xpm_file_to_image(mlx_ptr,
			objs->mat->txtr_name, size, size + 1);
	objs->mat->normal.img = mlx_xpm_file_to_image(mlx_ptr,
			objs->mat->nrml_name, size, size + 1);
	objs->mat->bump.img = mlx_xpm_file_to_image(mlx_ptr,
			objs->mat->bump_name, size, size + 1);
	if ((objs->mat->txtr_name && !objs->mat->texture.img)
		|| (objs->mat->nrml_name && !objs->mat->normal.img)
		|| (objs->mat->bump_name && !objs->mat->bump.img))
	{
		ft_putstr_fd(2, "Error\nFile for textures not found.\n");
		return (-1);
	}
	if (objs->mat->texture.img)
		set_adress(&(objs->mat->texture));
	if (objs->mat->normal.img)
		set_adress(&(objs->mat->normal));
	if (objs->mat->bump.img)
		set_adress(&(objs->mat->bump));
	return (0);
}

int	find_texture(void *mlx_ptr, t_solid *objs, t_param *par)
{
	int	sky_size[2];

	sky_size[0] = W_SKY;
	sky_size[1] = H_SKY;
	if (par->sky_name
		&& !(par->skybox.img = mlx_xpm_file_to_image(mlx_ptr, par->sky_name,
				sky_size, sky_size + 1)))
	{
		ft_putstr_fd(2, "Error\nFile for skybox not found.\n");
		free(par->sky_name);
		return (-1);
	}
	if (par->sky_name)
		set_adress(&par->skybox);
	free(par->sky_name);
	while (objs)
	{
		if (set_by_type(objs, mlx_ptr) == -1)
			return (-1);
		objs = objs->next;
	}
	return (0);
}

int	find_txt_col(t_ray_prop props, t_data *texture)
{
	t_2dfvec	uv;
	t_2dvec		iuv;

	if (props.inters.type == 's')
		uv = uv_sphere(props.normal);
	else if (props.inters.type == 't')
		uv = uv_triangle(props.inters, props);
	else if (props.inters.type == 'q')
		uv = uv_quad(props.inters, props);
	else if (props.inters.type == 'c')
		uv = uv_cylinder(props.inters, props);
	else
		return (0);
	iuv.x = (int)(WIDTH * uv.x);
	iuv.y = (int)(HEIGHT * uv.y);
	return (pixel_get(texture, iuv.x, iuv.y));
}

int	transfer_txt(t_ray_prop props, t_data *texture, t_2dvec transfer)
{
	t_2dfvec	uv;
	t_2dvec		iuv;

	if (props.inters.type == 's')
		uv = uv_sphere(props.normal);
	else if (props.inters.type == 't')
		uv = uv_triangle(props.inters, props);
	else if (props.inters.type == 'q')
		uv = uv_quad(props.inters, props);
	else if (props.inters.type == 'c')
		uv = uv_cylinder(props.inters, props);
	else
		return (0);
	iuv.x = (int)(WIDTH * uv.x) + transfer.x;
	iuv.y = (int)(HEIGHT * uv.y) + transfer.y;
	if (iuv.x >= WIDTH || iuv.x < 0)
		iuv.x = 0;
	if (iuv.y >= HEIGHT || iuv.y < 0)
		iuv.y = 0;
	return (pixel_get(texture, iuv.x, iuv.y));
}
