/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pow.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 14:18:56 by ldelmas           #+#    #+#             */
/*   Updated: 2021/02/11 16:20:28 by ldelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

double	pow_double(double val, double pow)
{
	if (pow > 1)
		return (val * pow_double(val, pow - 1));
	else if (pow == 1)
		return (val);
	return (0);
}
