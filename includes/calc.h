/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 17:24:52 by ldelmas           #+#    #+#             */
/*   Updated: 2021/04/13 12:34:16 by ldelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CALC_H
# define CALC_H

typedef struct s_2dfvec
{
	double	x;
	double	y;
}				t_2dfvec;

typedef struct s_3dfvec
{
	double	x;
	double	y;
	double	z;
}				t_3dfvec;

typedef struct s_4dfvec
{
	double	x;
	double	y;
	double	z;
	double	h;
}				t_4dfvec;

typedef struct s_2dvec
{
	int		x;
	int		y;
}				t_2dvec;

double			pow_double(double val, double pow);

double			*set_4dfarray(double x, double y, double z, double h);
double			*set_3dfarray(double x, double y, double z);

t_4dfvec		set_4dfvec(double x, double y, double z, double h);
t_3dfvec		set_3dfvec(double x, double y, double z);
t_2dfvec		set_2dfvec(double x, double y);
t_2dvec			set_2dvec(int x, int y);
double			length_3dfvec(t_3dfvec vctr);
t_3dfvec		scalprod_3dfvec(t_3dfvec u, double f);
double			dotprod_3dfvec(t_3dfvec a, t_3dfvec b);
t_3dfvec		vecprod_3dfvec(t_3dfvec u, t_3dfvec v);
t_3dfvec		vecadd_3dfvec(t_3dfvec u, t_3dfvec v);
t_3dfvec		vecmin_3dfvec(t_3dfvec u, t_3dfvec v);
t_2dfvec		norm_2df(t_2dfvec vctr);
t_3dfvec		normalize_ray(t_3dfvec vctr);
int				interval_3dfvec(t_3dfvec rot, double min, double max);

double			**set_matrix(t_2dvec dim);
double			**set_idmatrix(t_2dvec dim);
double			**set_transmatrix(double xaxis[3], double yaxis[3],
					double zaxis[3], double pos[3]);
double			**matrix_product(t_2dvec dim1, t_2dvec dim2,
					double **mat1, double **mat2);
double			**copy_matrix(t_2dvec dim, double **matrix);
void			print_matrix(t_2dvec dim, double **mtrx);

int				isbetween(double min, double max, double val);

#endif
