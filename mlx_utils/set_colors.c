/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_colors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 15:09:40 by ldelmas           #+#    #+#             */
/*   Updated: 2021/04/12 13:30:36 by ldelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	create_argb(char a, char r, char g, char b)
{
	char	argb_c[4];
	int		*argb_i;

	argb_c[3] = a;
	argb_c[2] = r;
	argb_c[1] = g;
	argb_c[0] = b;
	argb_i = (int *)argb_c;
	return (*argb_i);
}
