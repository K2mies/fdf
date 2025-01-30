/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 10:47:40 by rhvidste          #+#    #+#             */
/*   Updated: 2025/01/30 11:26:52 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fdf.h"

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

	//init	transform operations here
	t_matrix	scale;
	t_matrix	rot_x;
	t_matrix	rot_z;
	//t_matrix	translation;

	//remember that rotations take radians as arguments, not degree,
	// (M_PI / 2) = 90degree.

	
	// Create transform matricies here
	scale		= create_scaling_matrix(1.0, 1.0, 0.1);
	rot_x		= create_rotation_x_matrix(deg_to_rad(45));
	rot_z		= create_rotation_z_matrix(deg_to_rad(45));
	//translation = create_translation_matrix((data->width / 2.0), (data->height / 2.0), 0);
	//translation = create_translation_matrix(100, 100, 0);

	// Apply transform operations here (the order matters)
	multiply_points(data, &scale);
	multiply_points(data, &rot_z);
	multiply_points(data, &rot_x);
	//multiply_points(data, &translation);

	// ORTHOGRAPHIC PROJECTION
	//Here we handle the paramaters in a struct.
	t_matrix	orthographic;
	t_ortho_data	*o;
	o = malloc(sizeof(t_ortho_data));
	o->left = -50.0f;
	o->right = 50.0f;
	o->bottom = -50.0f;
	o->top = 50.0f;
	o->near = 0.1f;
	o->far = 100.0f;

	orthographic = create_orthographic_matrix(o);
	ortho_project(data, orthographic);

	//Function to center the projection to the center of screen. 
	//offset_view(data);
	
	// Function to get the Max and Min values of view space object
	get_max(data);

	//Function to return space to 0 pos (for scale operations()
	//center_view(data);
	
	// Function to scale in view space
	scale_view(data);
	
	// Recenter after scale operation.
	offset_view(data);

	// Draw the actual model
	draw(data);

	mlx_loop(mlx);
	mlx_delete_image(mlx, data->img);

	// free things left over.
	free(o);
	free_point_arr(data);
	free(data);

	//Terminate mlx;
	mlx_terminate(mlx);
	
	return (EXIT_SUCCESS);
}
