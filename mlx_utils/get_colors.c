/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_colors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 15:08:54 by ldelmas           #+#    #+#             */
/*   Updated: 2021/04/12 13:29:46 by ldelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	get_a(int *argb)
{
	char	*conv;

	conv = (char *)argb;
	return (*(conv + 3));
}

char	get_r(int *argb)
{
	char	*conv;

	conv = (char *)argb;
	return (*(conv + 2));
}

char	get_g(int *argb)
{
	char	*conv;

	conv = (char *)argb;
	return (*(conv + 1));
}

char	get_b(int *argb)
{
	char	*conv;

	conv = (char *)argb;
	return (*(conv));
}
