/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 10:47:40 by rhvidste          #+#    #+#             */
/*   Updated: 2025/02/04 15:51:58 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fdf.h"

int32_t	main(int argc, char **argv)
{
//	// Function to validate map
//	if (!(validate_map(argc, argv)))
//	{
//		ft_printf("map is invalid\n");
//		exit(EXIT_FAILURE);
//	}
//	
//	// INIT EVERYTHING
//	//init data	
//	t_data *data;
//	data = init_data();
//
//	// Get map paramaters
//	get_map_len(argv, data);
//	get_row_count(argv, data);
//	get_col_count(argv, data);
//	
//	//init all data structs
//	init_3d_points(data);
//	init_2d_points(data);
//	memset_points(data);
//	init_line_data(data);
//	init_gradient_data(data);

	t_data	*data;
	data = init_all(argc, argv);
	
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

	//Function to start mlx
	mlx_start(data);

	//print monitor dimensions
	printf("monitor x = %d\nmonitor y = %d\n", data->width, data->height);
	
	// FILL BACKGROUND COLOR HERE
	color_fill(data);
	
	//init	transform operations here
//	t_matrix	scale;
//	t_matrix	rot_x;
//	t_matrix	rot_z;
//	t_matrix	translation;

	//Remember that rotations take radians as arguments, not degree,
	//(M_PI / 2) = 90degree.
			
	// Create transform matricies here
//	scale		= create_scaling_matrix(1.0, 1.0, 1.0);
//	rot_x		= create_rotation_x_matrix(deg_to_rad(45));
//	rot_z		= create_rotation_z_matrix(deg_to_rad(45));
//	translation = create_translation_matrix((data->width / 2.0), (data->height / 2.0), 0);
//	translation = create_translation_matrix(0, 0, -50);


	// Apply transform operations here (the order matters)
//	multiply_points(data, &scale);
//	multiply_points(data, &rot_z);
//	multiply_points(data, &rot_x);
//	multiply_points(data, &translation);i
	orthographic_rotation(data);
	
	// ORTHOGRAPHIC PROJECTION
	ortho_projection(data);

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
	
	// Recenter after scale operation
	offset_view(data);

	// Draw the actual model
	draw(data);

	mlx_key_hook(data->mlx, &my_keyhook, data);
	mlx_loop(data->mlx);
	mlx_delete_image(data->mlx, data->img);

	// FREE THINGS LEFT OVER.
	// Function to free all
	free_all(data);

	//Terminate mlx;
	mlx_terminate(data->mlx);
	
	return (EXIT_SUCCESS);
}
