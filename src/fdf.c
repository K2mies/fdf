/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 10:47:40 by rhvidste          #+#    #+#             */
/*   Updated: 2025/01/31 17:28:20 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fdf.h"

// Function to start mlx
void	mlx_start(t_data *data)
{
	mlx_set_setting(MLX_MAXIMIZED, true);
//	mlx_t *mlx;
	if (!(data->mlx = mlx_init(WIDTH, HEIGHT, "FDF", true)))
		ft_error();
	mlx_get_monitor_size(0, &data->width, &data->height);
	data->img = mlx_new_image(data->mlx, data->width, data->height);
	if (!data->img || (mlx_image_to_window(data->mlx, data->img, 0, 0) < 0))
		ft_error();
}

// Function keyhook for escaping the program
void	my_keyhook(mlx_key_data_t keydata, void *param)
{
	t_data *data = (t_data *)param;
	// If we PRESS the 'ESCAPE' key, print "Hello".
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_RELEASE)
	{
		ft_printf("test = %d\n", data->width);
		puts("Escape!");
		free(data->o);
		free_point_arr(data);
		free(data);
		exit(EXIT_SUCCESS);
	}
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

	// Parse the 3d point array
	parse_points(argv, data);

	// Print the parsed maps
//	print_arr(data, 'x');
//	printf("\n");
//	print_arr(data, 'y');
//	printf("\n");
//	print_arr(data, 'z');
//	printf("\n");
//	print_arr(data, 'w');
//	printf("\n");
//	print_arr(data, 'c');

	// Function to get width and height of monitor and set mlx to those dimensions

//void	get_dimensions(t_data *data)
//{
//	mlx_set_setting(MLX_MAXIMIZED, true);
//	mlx_t	*mlx;
//	mlx = mlx_new_image(mlx, WIDTH)
//}

	//MLX ----------------------------------------------------------------------------
//	mlx_set_setting(MLX_MAXIMIZED, true);
//	mlx_t *mlx;
//	if (!(mlx = mlx_init(WIDTH, HEIGHT, "FDF", true)))
//		ft_error();
	//get monitor size here;
//	mlx_get_monitor_size(0, &data->width, &data->height);
//	data->img = mlx_new_image(mlx, data->width, data->height);
//	if (!data->img || (mlx_image_to_window(mlx, data->img, 0, 0) < 0))
//		ft_error();

	//Function to start mlx
	mlx_start(data);

	//print monitor dimensions
	printf("monitor x = %d\nmonitor y = %d\n", data->width, data->height);
	
	// FILL BACKGROUND COLOR HERE
	color_fill(data);
	
	//init	transform operations here
//	t_matrix	scale;
	t_matrix	rot_x;
	t_matrix	rot_z;
//	t_matrix	translation;

	//Remember that rotations take radians as arguments, not degree,
	//(M_PI / 2) = 90degree.
			
	// Create transform matricies here
//	scale		= create_scaling_matrix(1.0, 1.0, 1.0);
	rot_x		= create_rotation_x_matrix(deg_to_rad(45));
	rot_z		= create_rotation_z_matrix(deg_to_rad(45));
//	translation = create_translation_matrix((data->width / 2.0), (data->height / 2.0), 0);
//	translation = create_translation_matrix(0, 0, -50);


	// Apply transform operations here (the order matters)
//	multiply_points(data, &scale);
	multiply_points(data, &rot_z);
	multiply_points(data, &rot_x);
//	multiply_points(data, &translation);
	
	// ORTHOGRAPHIC PROJECTION
	//Here we handle the paramaters in a struct.
	
	// Function to init orthographic data
	t_matrix	orthographic;
	init_ortho_data(data);

	data->o->left = -50.0f;
	data->o->right = 50.0f;
	data->o->bottom = -50.0f;
	data->o->top = 50.0f;
	data->o->near = 0.1f;
	data->o->far = 100.0f;

//	t_matrix	orthographic;
//	t_ortho_data	*o;
//	o = malloc(sizeof(t_ortho_data));
//	o->left = -50.0f;
//	o->right = 50.0f;
//	o->bottom = -50.0f;
//	o->top = 50.0f;
//	o->near = 0.1f;
//	o->far = 100.0f;

	orthographic = create_orthographic_matrix(data->o);
	ortho_project(data, orthographic);

		
//	print_arr(data, 'c');
//	printf("\n");

	// PERSPECTIVE PROJECTION(not working yet, also need to edit 3d->2d function to handle w)
//	t_matrix	perspective;
//	perspective = create_perspective_matrix(60.0, (data->width / data->height), 1.0, 100.0);
//	perspective = create_perspective_matrix(45.0, 16.0 / 9.0, 1.0, 100.0);
//	multiply_points(data, &perspective);
//	ortho_project(data, perspective);

	
	//Function to center the projection to the center of screen. 
//	offset_view(data);
	
	// Function to get the Max and Min values of view space object
	get_max_and_min(data);

	//Function to return space to 0 pos (for scale operations()
//	center_view(data);
	
	// Function to scale in view space
	scale_view(data);
	
	// Recenter after scale operation.
	offset_view(data);

	// Draw the actual model
	draw(data);

	mlx_key_hook(data->mlx, &my_keyhook, data);
	mlx_loop(data->mlx);
	mlx_delete_image(data->mlx, data->img);

	// FREE THINGS LEFT OVER.
	// Frees orthographic scturct
	free(data->o);
	// Frees both 3d and 2d array
	free_point_arr(data);
	// Frees global data
	free(data);

	//Terminate mlx;
	mlx_terminate(data->mlx);
	
	return (EXIT_SUCCESS);
}
