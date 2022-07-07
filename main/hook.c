/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 14:31:19 by ldelmas           #+#    #+#             */
/*   Updated: 2022/07/07 11:04:34 by lucas            ###   ########.fr       */
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
	if (keycode == LEFT_KEY)
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
	else if (keycode == RIGHT_KEY)
	{
		(vars->ref)++;
		if (!(vars->images[vars->ref]))
			vars->ref = 0;
		show_image((vars->images)[vars->ref], vars->img, vars->screen);
		mlx_clear_window(vars->mlx, vars->win);
		mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
	}
	else
		printf("Non attributed key.\n");
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
	if (keycode == ESCAPE_KEY)
		key_exit(vars);
	else
		move_by_arrows(keycode, vars);
	return (1);
}
