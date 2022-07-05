/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 14:31:19 by ldelmas           #+#    #+#             */
/*   Updated: 2021/04/12 12:04:29 by ldelmas          ###   ########.fr       */
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
#include <stdio.h>

static void	move_by_arrows(int keycode, t_vars *vars)
{
	if (keycode == 123)
	{
		(vars->ref)--;
		if (vars->ref < 0)
		{
			vars->ref = 0;
			while ((vars->images)[vars->ref + 1])
				(vars->ref)++;
		}
		show_image((vars->images)[vars->ref], vars->img, vars->screen);
		mlx_clear_window(vars->mlx, vars->win);
		mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
	}
	else if (keycode == 124)
	{
		(vars->ref)++;
		if (!(vars->images[vars->ref]))
			vars->ref = 0;
		show_image((vars->images)[vars->ref], vars->img, vars->screen);
		mlx_clear_window(vars->mlx, vars->win);
		mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
	}
}

int	key_exit(t_vars *vars)
{
	free_images(vars->images, vars->screen);
	mlx_destroy_window(vars->mlx, vars->win);
	system("leaks miniRT");
	exit(EXIT_SUCCESS);
}

int	key_hook(int keycode, t_vars *vars)
{
	if (keycode == 53)
		key_exit(vars);
	else if (keycode > 122 && keycode < 125)
		move_by_arrows(keycode, vars);
	else
		printf("Non attributed key.\n");
	return (1);
}
