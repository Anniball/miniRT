/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_screen_size.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 12:21:32 by ldelmas           #+#    #+#             */
/*   Updated: 2022/07/05 10:44:33 by ldelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "../includes/main.h"

void	set_screen_size(t_2dvec *screen, void *mlx)
{
	t_2dvec	max;

	mlx_get_screen_size(mlx, &(max.x), &(max.y));
	if (screen->x > max.x)
		screen->x = max.x;
	if (screen->y > max.y)
		screen->y = max.y;
}
