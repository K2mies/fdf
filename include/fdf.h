/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 10:29:55 by rhvidste          #+#    #+#             */
/*   Updated: 2025/01/28 16:19:28 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../lib/libft/libft.h"
# include "../lib/MLX42/include/MLX42/MLX42.h"
# include <math.h>
# include <fcntl.h>
# include <stdint.h>
# include <stdio.h>

//# define WIDTH 2048
//# define HEIGHT 2048
# define WIDTH 3840
# define HEIGHT 2160

# define RED	0xFF0000FF
# define GREEN	0x00FF00FF
# define BLUE	0x0000FFFF
# define WHITE	0xFFFFFFFF
# define BLACK	0x000000FF

// Define a t_vec4 data structure
typedef struct		s_vec4
{
		double			x;
		double			y;
		double			z;
		double			w;
		unsigned int	rgba;
}		t_vec4;

// Define a 2d vector structure
typedef struct		s_vec2
{
		double		x;
		double		y;
}		t_vec2;

//Define a 4x4 matrix structure
typedef struct		s_matrix
{
		double		m[4][4];
}		t_matrix;


//Define a orthographic data struct
typedef struct		s_ortho_data
{
		double		left;
		double		right;
		double		bottom;
		double		top;
		double		near;
		double		far;
}		t_ortho_data;

// Define a global data structure
typedef struct 		s_data
{
		int			width;
		int			height;
		int			len;
		int			rows;
		int			cols;
		int			fd;
		char		*line;
		mlx_image_t *img;
		t_vec4		**points;
		t_vec2		**p2d;
}		t_data;


// Read map functions------------------------------------------------------------------
int			print_map(char **argv);
int			get_row_count(char **argv, t_data *data);
int			get_col_count(char **argv, t_data *data);
int			get_map_len(char **argv, t_data *data);
int			word_count(const char *str);
int			print_arr(t_data *data, char flag);
// Parse map--------------------------------------------------------------------------
int			parse_points(char **argv, t_data *data);
int			reset_parse(char **argv, t_data *data, char **split, char **split2);
int			parse_xy_points(t_data *data);
int			parse_z_points(t_data *data, char **split, char **split2);
int			parse_rgba_points(t_data *data, char **split, char **split2);
// Init data---------------------------------------------------------------------------
t_data		*init_data();
void		init_3d_points(t_data *data);
void		init_2d_points(t_data *data);
void		memset_points(t_data *data);
// Matrix operations-------------------------------------------------------------------
t_matrix	create_empty_matrix(void);
t_matrix	create_identity_matrix(void);
t_vec4		matrix_multiply_vector(t_matrix m, t_vec4 v);
t_vec4		normalize_homogeneous_vector(t_vec4 v);
// Matrix transformations--------------------------------------------------------------
t_matrix	create_scaling_matrix(double sx, double sy, double sz);
t_matrix	create_rotation_x_matrix(double angle);
t_matrix	create_rotation_y_matrix(double angle);
t_matrix	create_rotation_z_matrix(double angle);
t_matrix	create_translation_matrix(double tx, double ty, double tz);
// Matrix projection-------------------------------------------------------------------
t_matrix	create_orthographic_matrix(t_ortho_data *o);
t_matrix	create_perspective_matrix(double fov, double ar, double n, double f);
void		project_3d_to_2d(t_vec4 v, t_matrix m, t_vec2 *res);
// Line draw---------------------------------------------------------------------------
void		draw_line(t_data *data, int x0, int y0, int x1, int y2, uint32_t color);
// Utils-------------------------------------------------------------------------------
double		deg_to_rad(double degrees);
void		free_point_arr(t_data *data);
void		free_arr(char **arr);

#endif
