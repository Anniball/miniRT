/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 10:40:55 by ldelmas           #+#    #+#             */
/*   Updated: 2021/04/19 15:06:17 by ldelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READ_H
# define READ_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include "calc.h"
# include "geom.h"

# define BUFFER_SIZE 100

typedef struct s_camera
{
	double		fov;
	t_3dfvec	*position;
	t_3dfvec	*orientation;
	void		*next;
}				t_camera;

typedef struct s_param
{
	t_solid		*objs;
	t_light		*lights;
	t_camera	*cams;
	char		filter;
	int			aa;
	char		mult;
	char		*sky_name;
	t_data		skybox;
}				t_param;

t_param			*read_file(char *filename, t_2dvec *res, t_param *par);
int				set_objs(char *ln, t_solid **o,
					t_light **lights, t_camera **cam);
t_camera		*set_cam(char *line, t_camera *next);
t_light			*set_lighting(char type, char *line, t_light *lights);
t_solid			*set_solid(char type, char *line, t_solid *objs);
t_material		*check_mat(char **str);

int				get_next_line(int fd, char **line);

int				ft_strlen(const char *s1);
void			ft_putstr_fd(int fd, char *str);
char			*ft_strdup(const char *s1);
int				ft_isspace(char c);
int				ft_isdigit(char c);
int				ft_atoi(const char *str);
double			ft_atof(const char *str);
int				ft_strcmp(const char *s1, const char *s2);

t_3dfvec		*get_fvals(char **str);
double			get_fval(char **str);
int				get_val(char **str);
int				*get_col(char **str);

void			free_objects(t_solid *objs, t_light *lights, t_camera *cam);

#endif
