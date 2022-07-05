/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 15:35:54 by ldelmas           #+#    #+#             */
/*   Updated: 2022/07/05 12:55:05 by ldelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/read.h"
#include "../includes/calc.h"
#include "../includes/geom.h"
#include "../includes/main.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

static char	*check_name(char *ln)
{
	int		i;
	char	*name;

	while (ft_isspace(*ln))
		ln++;
	i = 0;
	while (ln[i])
		i++;
	if (ln[i - 1] != 'm' || ln[i - 2] != 'p'
		|| ln[i - 3] != 'x' || ln[i - 4] != '.')
		return ((void *)0);
	name = malloc(sizeof(*name) * (i + 1));
	if (!name)
		return ((void *)0);
	name[i] = '\0';
	while (i--)
		name[i] = ln[i];
	printf("Skybox : %s\n", name);
	return (name);
}

static int	get_filter_thread(char *ln, t_param *par)
{
	int	ret;

	ret = 1;
	if (ln[0] == 's' && ln[1] == 'e' && ln[2] == 'p' && !(ln[3]))
		par->filter = 's';
	else if (ln[0] == 'm' && ln[1] == 'u' && ln[2] == 'l' && !(ln[3]))
		par->mult = 1;
	else if (ln[0] == 's' && ln[1] == 'k' && ln[2] == 'y' && ft_isspace(ln[3]))
	{
		par->sky_name = check_name(ln + 3);
		if (!par->sky_name)
			return (-1);
	}
	else
		ret = 0;
	return (ret);
}

static int	get_antialiasing(char *ln, t_param *par)
{
	if (ln[0] == 'a' && ln[1] == 'a')
	{
		ln += 2;
		par->aa = get_val(&ln);
		return ((int)par->aa);
	}
	return (0);
}

int	get_bonus(char *ln, t_param *par)
{
	int	val;

	val = 0;
	val = get_filter_thread(ln, par);
	if (!val)
		val = get_antialiasing(ln, par);
	if (val > 0)
		free(ln);
	if (val < 0)
	{
		printf("Error\nValue of a bonus isn't right.\n");
		return (0);
	}
	return (val);
}

void	set_bonus(t_param *par)
{
	par->filter = '\0';
	par->aa = 1;
	par->mult = 0;
	par->sky_name = (void *)0;
	par->skybox.img = (void *)0;
}
