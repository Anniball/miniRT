/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 09:52:25 by ldelmas           #+#    #+#             */
/*   Updated: 2021/04/13 12:36:27 by ldelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_UTILS_H
# define MLX_UTILS_H

# include "../includes/calc.h"

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

void			pixel_put(t_data *data, int x, int y, int color);
int				pixel_get(t_data *data, int x, int y);

char			get_a(int *argb);
char			get_r(int *argb);
char			get_g(int *argb);
char			get_b(int *argb);
int				create_argb(char a, char r, char g, char b);
int				add_color(int color, int add);

int				open_bmp(t_2dvec size, int **image);

#endif
