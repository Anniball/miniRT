/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 14:31:02 by ldelmas           #+#    #+#             */
/*   Updated: 2021/04/12 13:29:13 by ldelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../includes/read.h"
#include "../includes/mlx_utils.h"

static void	set_file_header(int fd, t_2dvec size)
{
	int		i;
	char	header[14];
	int		stride;
	int		f_size;

	i = -1;
	while (++i < 14)
		header[i] = 0;
	stride = (size.x * 3) + ((4 - (size.x * 3) % 4) % 4);
	f_size = 54 + (size.y * stride);
	header[0] = (unsigned char)('B');
	header[1] = (unsigned char)('M');
	header[2] = (unsigned char)(f_size);
	header[3] = (unsigned char)(f_size >> 8);
	header[4] = (unsigned char)(f_size >> 16);
	header[5] = (unsigned char)(f_size >> 24);
	header[10] = 54;
	write(fd, header, sizeof(header));
}

static void	set_info_header(int fd, t_2dvec size)
{
	char	header[40];
	int		i;

	i = -1;
	while (++i < 40)
		header[i] = 0;
	header[0] = (unsigned char)(40);
	header[4] = (unsigned char)(size.x);
	header[5] = (unsigned char)(size.x >> 8);
	header[6] = (unsigned char)(size.x >> 16);
	header[7] = (unsigned char)(size.x >> 24);
	header[8] = (unsigned char)(size.y);
	header[9] = (unsigned char)(size.y >> 8);
	header[10] = (unsigned char)(size.y >> 16);
	header[11] = (unsigned char)(size.y >> 24);
	header[12] = 1;
	header[14] = 24;
	write(fd, header, sizeof(header));
}

static void	set_info_colors(int fd, t_2dvec size, int **image)
{
	int				i;
	int				j;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	i = size.y;
	while (--i >= 0)
	{
		j = -1;
		while (++j < size.x)
		{
			r = (unsigned char)(get_r(image[j] + i));
			g = (unsigned char)(get_g(image[j] + i));
			b = (unsigned char)(get_b(image[j] + i));
			write(fd, &b, 1);
			write(fd, &g, 1);
			write(fd, &r, 1);
		}
	}
}

int	open_bmp(t_2dvec size, int **image)
{
	int	fd;

	fd = open("save.bmp", O_CREAT | O_WRONLY | O_TRUNC, 77777);
	ft_putstr_fd(1, "Saving as bmp.\n");
	if (fd == -1)
	{
		ft_putstr_fd(2, "Error\nBad reading of the file.\n");
		return (-1);
	}
	set_file_header(fd, size);
	set_info_header(fd, size);
	set_info_colors(fd, size, image);
	if (close(fd) < 0)
	{
		ft_putstr_fd(2, "Error\nCouldn't correctly close the bmp file.\n");
		return (-1);
	}
	return (fd);
}
