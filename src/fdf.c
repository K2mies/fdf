/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 10:47:40 by rhvidste          #+#    #+#             */
/*   Updated: 2025/01/27 18:18:40 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fdf.h"

static void	ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

int32_t	main(int argc, char **argv)
{
	if (argc != 2)
		return (0);

	t_data *data;
	data = init_data();
	
	get_map_len(argv, data);
	get_row_count(argv, data);
	get_col_count(argv, data);
	
	init_3d_points(data);
	init_2d_points(data);
	memset_points(data);
	
	ft_printf("len = %d\nrows = %d\ncolumns = %d\n", data->len, data->rows, data->cols);
	//print_map(argv);
	//memset_points(data); // you do not need memset anymore as calloc initalizes the points.
	
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

	//DO STUFF HERE
	//draw_line(data, 20, 0, 20, 100, WHITE);

	//printf("%.1f, %.1f", data->points[2][7].x, data->points[2][7].y);

	//Apply transform operations here

	//Apply projection operations here

	// test output

	//translate every value.
	t_matrix	scale;
	t_matrix	rot_x;
	t_matrix	translation;

	scale		= create_scaling_matrix(4.0, 4.0, 4.0);
	rot_x		= create_rotation_x_matrix(15);
	translation = create_translation_matrix(100, 100, 0);

	int		i = 0;
	int		j = 0;
	while (i < data->rows)
	{
		j = 0;
		while (j < data->cols)
		{
			
			data->points[i][j] = matrix_multiply_vector(scale, data->points[i][j]);	
			data->points[i][j] = matrix_multiply_vector(rot_x, data->points[i][j]);
			data->points[i][j] = matrix_multiply_vector(translation, data->points[i][j]);
			j++;
		}
		i++;
	}

	//Here we handle an orthographic projection.
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
	//t_vec4	p3d1 = data->points[1][1];
	//t_vec4	p3d2 = data->points[1][2];
	//printf("4d Vector result(%2.f, %2.f, %2.f, %2.f)\n", p3d2.x, p3d2.y, p3d2.z, p3d2.w);

	//t_vec2	p1;
	//t_vec2	p2;
	//project_3d_to_2d(p3d1, orthographic, &p1);
	//project_3d_to_2d(p3d2, orthographic, &p2);

	//printf("2d Vector result(%2.f, %2.f)", p2.x, p2.y);
	// Line drawing
	//draw_line(data, (int)p1.x, (int)p1.y, (int)p2.x, (int)p2.y, WHITE);
	// Line drawing loop
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

	i = 0;
	j = 0;
	while (i < data->rows)
	{
		j = 0;
		while (j < data->cols)
		{
			printf("%d, %d ", (int)data->p2d[i][j].x, (int)data->p2d[i][j].y);
			if (i < data->rows - 1 && j < data->cols -1)
			{
				draw_line(data, (int)data->p2d[i][j].x, (int)data->p2d[i][j].y, (int)data->p2d[i + 1][j].x, (int)data->p2d[i + 1][j].y, WHITE); //rows
				draw_line(data, (int)data->p2d[i][j].x, (int)data->p2d[i][j].y, (int)data->p2d[i][j + 1].x, (int)data->p2d[i][j + 1].y, WHITE); //cols
			}
			//printf("%2.f, %2.f", data->p2d[i][j].x, data->p2d[i][j].y);
			j++;
		}
		printf("\n");
		i++;
	}
	mlx_loop(mlx);
	mlx_terminate(mlx);
	
	free(o);
	free_point_arr(data);
	free(data);
	return (EXIT_SUCCESS);
}
