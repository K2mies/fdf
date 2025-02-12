/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 10:29:55 by rhvidste          #+#    #+#             */
/*   Updated: 2025/02/12 14:16:16 by rhvidste         ###   ########.fr       */
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
# include <stdbool.h>

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
typedef struct s_vec4
{
	double			x;
	double			y;
	double			z;
	double			w;
	unsigned int	rgba;
}	t_vec4;

// Define a 2d vector structure
typedef struct s_vec2
{
	double			x;
	double			y;
	unsigned int	rgba;
}	t_vec2;

//Define a 4x4 matrix structure
typedef struct s_matrix
{
	double		m[4][4];
}	t_matrix;

//Define a orthographic data struct
typedef struct s_ortho_data
{
	double		left;
	double		right;
	double		bottom;
	double		top;
	double		near;
	double		far;
}	t_ortho_data;

// Define a perspective data struct
typedef struct s_perspective_data
{
	double		fov;
	double		ar;
	double		n;
	double		f;
}	t_perspective_data;

//Define a line data struct
typedef struct s_line_data
{
	int				dx;
	int				sx;
	int				dy;
	int				sy;
	int				err;
	int				e2;
	int				x0;
	int				y0;
	int				x1;
	int				y1;
	int				len;
	int				pix;
	unsigned int	color;
}	t_line_data;

// Define a gradient data struct
typedef struct s_gradient_data
{
	int		start_r;
	int		start_g;
	int		start_b;
	int		end_r;
	int		end_g;
	int		end_b;
	int		alpha;
}	t_gradient_data;

// Define a global data structure
typedef struct s_data
{
	int					width;
	int					height;
	double				x_max;
	double				y_max;
	double				x_min;
	double				y_min;
	double				trans_x;
	double				trans_y;
	double				trans_z;
	double				zoom;
	int					len;
	int					rows;
	int					cols;
	int					fd;
	char				*line;
	char				**split;
	char				flag;
	char				**argv;
	int					argc;
	mlx_image_t			*img;
	mlx_t				*mlx;
	t_vec4				**points;
	t_vec4				**proj;
	t_vec2				**p2d;
	t_ortho_data		*o;
	t_perspective_data	*p;
	t_line_data			*ld;
	t_gradient_data		*gd;
}	t_data;

// Read map functions---------------------------------------------------
int			get_row_count(char **argv, t_data *data);
int			get_col_count(char **argv, t_data *data);
int			get_map_len(char **argv, t_data *data);
int			word_count(const char *str);
int			print_arr(t_data *data, char flag);
// Parse map-----------------------------------------------------------
int			parse_points(char **argv, t_data *data);
int			reset_parse(char **argv, t_data *data);
int			parse_xy_points(t_data *data);
int			parse_z_points(t_data *data, char **split, char **split2);
int			parse_rgba_points(t_data *data, char **split, char **split2);
// Init data-----------------------------------------------------------
t_data		*init_all(int argc, char **argv);
t_data		*init_data(void);
void		init_gradient_data(t_data *data);
void		init_line_data(t_data *data);
// Init array----------------------------------------------------------
void		copy_arr_data(t_data *data, t_vec4 **dest, t_vec4 **src);
void		init_proj_points(t_data *data);
void		init_3d_points(t_data *data);
void		init_2d_points(t_data *data);
void		memset_points(t_data *data);
// Matrix operations---------------------------------------------------
t_matrix	create_empty_matrix(void);
t_matrix	create_identity_matrix(void);
t_vec4		matrix_multiply_vector(t_matrix m, t_vec4 v);
t_vec4		normalize_homogeneous_vector(t_vec4 v);
// Matrix transformations----------------------------------------------
t_matrix	create_scaling_matrix(double sx, double sy, double sz);
t_matrix	create_rotation_x_matrix(double angle);
t_matrix	create_rotation_y_matrix(double angle);
t_matrix	create_rotation_z_matrix(double angle);
t_matrix	create_translation_matrix(double tx, double ty, double tz);
// Transform operations-----------------------------------------------
void		orthographic_rotation(t_data *data);
// Matrix projection---------------------------------------------------
void		multiply_points(t_data *data, t_matrix *matrix);
void		multiply_projection_points(t_data *data, t_matrix *matrix);
//Orthograpihc projection---------------------------------------------
void		ortho_projection(t_data *data);
void		init_ortho_data(t_data *data);
t_matrix	create_orthographic_matrix(t_ortho_data *o);
void		project_3d_to_2d(t_vec4 v, t_matrix m, t_vec2 *res);
void		ortho_project(t_data *data, t_matrix orthographic);
//Perspective projection---------------------------------------------
void		init_perspective_data(t_data *data);
void		perspective_projection(t_data *d);
t_matrix	create_perspective_matrix(double fov, double ar,
				double n, double f);
void		perspective_project(t_data *data, t_matrix perspective);
void		perspective_project_3d_to_2d(t_vec4 v, t_matrix m,
				t_vec2 *res);
//3D operations-----------------------------------------------------
double		get_3d_max(t_data *data);
void		project(t_data *data);
// Line draw--------------------------------------------------------
void		draw_line(t_data *data, t_vec2 p0, t_vec2 p1);
// Draw operations--------------------------------------------------
void		color_fill(t_data *data);
void		draw(t_data *data);
// 2d operations----------------------------------------------------
void		redraw(t_data *data);
void		scale_view(t_data *data);
void		offset_view(t_data *data);
void		center_view(t_data *data);
void		get_max_and_min(t_data *data);
// Utils------------------------------------------------------------
double		deg_to_rad(double degrees);
void		free_point_arr(t_data *data, char flag);
void		free_arr(char **arr);
int			arr_len(char **arr);
void		free_all(t_data *data);
// Mlx ------------------------------------------------------------
void		mlx_start(t_data *data);
void		my_keyhook(mlx_key_data_t keydata, void *param);
// Keyhooks 01------------------------------------------------------
void		r_keyhook(void *param);
void		tz_keyhook(void *param);
void		tx_keyhook(void *param);
void		ty_keyhook(void *param);
// Keyhooks 02-----------------------------------------------------
void		esc_keyhook(void *param);
void		reset_keyhook(void *param);
void		p_keyhook(void *param);
void		z_keyhook(double xdelta, double ydelts, void *param);
// Keyhook functrions
void		scroll_up(double ydelta, t_data *data);
void		scroll_down(double ydelta, t_data *data);
void		rotate(t_data *data, double x, double y, double z);
// Error-----------------------------------------------------------
void		ft_error(void);
bool		validate_map(int argc, char **argv);
// Line draw utils-------------------------------------------------
int			clamp(int value, int min, int max);
int			calculate_line_length(int x1, int y1, int x2, int y2);
int			is_valid(t_data *data);
int			extract_channel(int color, int shift);
#endif
