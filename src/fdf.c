/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 10:47:40 by rhvidste          #+#    #+#             */
/*   Updated: 2025/01/28 16:19:23 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fdf.h"

// Function to fill the background with black useing put_pixel()
void	color_fill(t_data *data)
{
	uint32_t	i;
	uint32_t	j;

	i = 0;
	j = 0;
	while (i < data->img->width)
	{
		j = 0;
		while (j < data->img->height)
		{
			mlx_put_pixel(data->img, i, j, BLACK);
			j++;
		}
		i++;
	}
}

// Function to apply matrix transformation to all 3d point vec4 vectors
void multiply_points(t_data *data, t_matrix *matrix)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < data->rows)
	{
		j = 0;
		while(j < data->cols)
		{
			data->points[i][j] = matrix_multiply_vector(*matrix, data->points[i][j]);
			j++;
		}
		i++;
	}
}

// Function to project into 2d space with orthographic projection. 
void	ortho_project(t_data *data, t_matrix orthographic)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < data->rows)
	{
		j = 0;
		while (j < data->cols)
		{
			project_3d_to_2d(data->points[i][j], orthographic, &data->p2d[i][j]);
			j++;
		}
		i++;
	}
}

// Function to draw the whole grid
void draw(t_data *data)
{
    int i; 
	int j;

    i = 0;
    while (i < data->rows)
    {
        j = 0;
        while (j < data->cols)
        {
            if (i < data->rows - 1)
                draw_line(data, (int)data->p2d[i][j].x, (int)data->p2d[i][j].y, 
                          (int)data->p2d[i + 1][j].x, (int)data->p2d[i + 1][j].y, WHITE);
            if (j < data->cols - 1)
                draw_line(data, (int)data->p2d[i][j].x, (int)data->p2d[i][j].y, 
                          (int)data->p2d[i][j + 1].x, (int)data->p2d[i][j + 1].y, WHITE);
            j++;
        }
        i++;
    }
}


// Error function for mlx
static void	ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

int32_t	main(int argc, char **argv)
{
	if (argc != 2)
		return (0);
	//init data	
	t_data *data;
	data = init_data();

	// Get map paramaters
	get_map_len(argv, data);
	get_row_count(argv, data);
	get_col_count(argv, data);
	
	//init point arrays
	init_3d_points(data);
	init_2d_points(data);
	memset_points(data);
	
	// Print paramaters for data
	ft_printf("len = %d\nrows = %d\ncolumns = %d\n", data->len, data->rows, data->cols);

	// Print the parsed maps
	parse_points(argv, data);
	print_arr(data, 'x');
	printf("\n");
	print_arr(data, 'y');
	printf("\n");
	print_arr(data, 'z');
	printf("\n");
	print_arr(data, 'w');
	printf("\n");
	print_arr(data, 'c');

	//MLX ----------------------------------------------------------------------------
	mlx_set_setting(MLX_MAXIMIZED, true);
	mlx_t *mlx = mlx_init(WIDTH, HEIGHT, "FDF", true);
	data->img = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!data->img || (mlx_image_to_window(mlx, data->img, 0, 0) < 0))
		ft_error();
	//get monitor size here;
	mlx_get_monitor_size(0, &data->width, &data->height);
	//print monitor dimensions
	printf("monitor x = %d\nmonitor y = %d\n", data->width, data->height);
	
	// FILL BACKGROUND COLOR HERE
	color_fill(data);

	//init	translate operations here
	t_matrix	scale;
	t_matrix	rot_x;
	t_matrix	rot_z;
	t_matrix	translation;

	//remember that rotations take radians as arguments, not degree,
	// (M_PI / 2) = 90degree.

	// Create transform matricies here
	scale		= create_scaling_matrix(4.0, 4.0, 4.0);
	rot_x		= create_rotation_x_matrix(deg_to_rad(45));
	//rot_z		= create_rotation_z_matrix(M_PI / 2);
	rot_z		= create_rotation_z_matrix(deg_to_rad(45));
	translation = create_translation_matrix(100, 100, 0);

	// Apply transform operations here (the order matters)
	multiply_points(data, &scale);
	multiply_points(data, &rot_z);
	multiply_points(data, &rot_x);
	multiply_points(data, &translation);

	// ORTHOGRAPHIC PROJECTION
	//Here we handle the paramaters in a struct.
	t_matrix	orthographic;
	t_ortho_data	*o;
	o = malloc(sizeof(t_ortho_data));
	o->left = -10.0f;
	o->right = 10.0f;
	o->bottom = -7.5f;
	o->top = 7.5f;
	o->near = 0.1f;
	o->far = 100.0f;

	orthographic = create_orthographic_matrix(o);
	ortho_project(data, orthographic);
	
	// Draw the actual model
	draw(data);

	mlx_loop(mlx);
	mlx_delete_image(mlx, data->img);
	mlx_terminate(mlx);
	
	free(o);
	free_point_arr(data);
	free(data);
	return (EXIT_SUCCESS);
}
