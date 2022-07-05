/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 14:20:47 by ldelmas           #+#    #+#             */
/*   Updated: 2022/07/05 12:53:21 by ldelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <math.h>
#include <stdlib.h>
#include "includes/calc.h"
#include "includes/geom.h"
#include "includes/mlx_utils.h"
#include "includes/read.h"
#include "includes/main.h"
#include "includes/bonus.h"
#include <stdio.h>

static t_param	*initialize_param(t_2dvec *screen, char *name)
{
	t_param	*param;

	param = malloc(sizeof(*param));
	if (!param)
		return ((void *)0);
	param->lights = (void *)0;
	param->cams = (void *)0;
	param->objs = (void *)0;
	set_bonus(param);
	param = read_file(name, screen, param);
	if (!param)
		return ((void *)0);
	if (screen->x <= 0 || screen->y <= 0)
	{
		ft_putstr_fd(1, "Error\nWrong values for resolution.\n");
		free_objects(param->objs, param->lights, param->cams);
		free(param->sky_name);
		free(param);
		return ((void *)0);
	}
	return (param);
}

static t_param	*set_param(t_2dvec *screen, char *name, void *mlx)
{
	t_param	*param;
	int		i;

	i = 0;
	while (name[i])
		i++;
	if (name[i - 1] != 't' || name[i - 2] != 'r' || name[i - 3] != '.')
	{
		printf("Error\nFile's name should end with '.rt'\n");
		return ((void *)0);
	}
	param = initialize_param(screen, name);
	if (!param)
		return ((void *)0);
	else if (find_texture(mlx, param->objs, param) == -1)
	{
		free_objects(param->objs, param->lights, param->cams);
		free(param);
		return ((void *)0);
	}
	set_screen_size(screen, mlx);
	return (param);
}

static t_vars	set_vars(t_vars vars, t_param *param)
{
	printf("Setting window. Resolution : (%d, %d)\n",
		vars.screen.x, vars.screen.y);
	vars.win = mlx_new_window(vars.mlx,
			vars.screen.x, vars.screen.y, "miniRT");
	vars.img.img = mlx_new_image(vars.mlx, vars.screen.x, vars.screen.y);
	vars.img.addr = mlx_get_data_addr(vars.img.img,
			&(vars.img.bits_per_pixel),
			&(vars.img.line_length),
			&(vars.img.endian));
	if (!vars.win || !vars.img.img || !vars.img.addr)
		return (vars);
	vars.images = get_images(param, vars.screen);
	if (!vars.images)
		return (vars);
	vars.ref = 0;
	return (vars);
}

static int	cases(t_vars vars, t_param *param, int argc, char **argv)
{
	vars = set_vars(vars, param);
	if (!vars.win || !vars.img.img || !vars.img.addr || !vars.images)
		return (-1);
	if (argc == 3 && ft_strcmp(argv[2], "--save"))
	{
		open_bmp(vars.screen, *(vars.images));
		free_images(vars.images, vars.screen);
		return (0);
	}
	show_image((vars.images)[vars.ref], vars.img, vars.screen);
	mlx_put_image_to_window(vars.mlx, vars.win, vars.img.img, 0, 0);
	printf("Image put to window!\n");
	mlx_hook(vars.win, 2, 1L << 0, key_hook, &vars);
	mlx_hook(vars.win, 17, 1L << 17, key_exit, &vars);
	mlx_loop(vars.mlx);
	return (0);
}

int	main(int argc, char **argv)
{
	t_vars	vars;
	t_param	*param;

	printf("Code begin.\n");
	if (!(argc == 2 || (argc == 3 && ft_strcmp(argv[2], "--save"))))
	{
		printf("Error\nProgram should only have a file's name as parameter.\n");
		return (-1);
	}
	vars.mlx = mlx_init();
	if (!vars.mlx)
		return (-1);
	param = set_param(&(vars.screen), argv[1], vars.mlx);
	if (!param)
		return (-1);
	if (!(cases(vars, param, argc, argv)))
		exit(EXIT_SUCCESS);
	return (-1);
}
