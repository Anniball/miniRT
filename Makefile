# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/17 10:52:21 by ldelmas           #+#    #+#              #
#    Updated: 2022/07/05 13:07:28 by ldelmas          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

FLAGS = -Wall -Wextra -Werror -I includes

%.o: %.c
			$(CC) $(FLAGS) -c $< -o $@

LIBX =	-L. -lmlx

CALC =	calc/set_vec.c	calc/isbetween.c	calc/norm_vec.c	calc/set_matrix.c\
		calc/mult_matrix.c	calc/set_array.c	calc/print_matrix.c\
		calc/copy_matrix.c	calc/length_vec.c	calc/dotprod.c	calc/vecprod.c\
		calc/pow.c	calc/scalprod.c	calc/vecadd.c	calc/vecmin.c\
		calc/vec_interval.c

GEOM =	geom/quad.c	geom/set_param.c	geom/set_trans.c	geom/set_point.c\
		geom/sphere.c	geom/triangle.c	geom/plane.c	geom/light.c\
		geom/drop_shadow.c	geom/intersection.c	geom/cylinder.c\
		geom/material.c	geom/light_operations.c	geom/set_light.c\
		geom/set_cylinder.c

READ =	read/ft_atof.c	read/ft_atoi.c	read/ft_putstr_fd.c	read/ischar.c\
		read/get_next_line_utils.c	read/get_next_line.c	read/get_scene.c\
		read/get_vals.c	read/get_col.c	read/set_solid.c	read/set_cam.c\
		read/set_lighting.c	read/ft_strcmp.c	read/set_objs.c	read/check_mat.c

MLXU =	mlx_utils/put_pixel.c	mlx_utils/get_colors.c	mlx_utils/set_colors.c\
		mlx_utils/add_colors.c	mlx_utils/bmp.c

MAIN =	main/free.c	main/translate.c	main/images.c	main/hook.c\
		main/set_screen_size.c	main/translate_utils.c

BONS =	bonus/get_bonus.c	bonus/filter.c	bonus/antialiasing.c\
		bonus/multithreading.c	bonus/uv_mapping.c	bonus/normal_mapping.c\
		bonus/color_mapping.c	bonus/bonus_mat.c	bonus/find_texture.c\
		bonus/background.c	bonus/mipmap.c

SRC = ${CALC} ${GEOM} ${MLXU} ${READ} ${BONS} ${MAIN} main.c

OBJS = ${SRC:.c=.o}

NAME = miniRT

all: 		${NAME}

${NAME}:	$(OBJS)
			$(CC) $(FLAGS) -o $(NAME) $(OBJS) $(LIBX)

clean:
			rm -f ${OBJS}

fclean: 	clean
			rm -f ${NAME}

re: 		fclean all

norm:		
			norminette ${SRC}
			norminette includes/

.PHONY:		all clean fclean re
