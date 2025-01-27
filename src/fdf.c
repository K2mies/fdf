/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 10:47:40 by rhvidste          #+#    #+#             */
/*   Updated: 2025/01/27 10:28:38 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fdf.h"

int	main(int argc, char **argv)
{
	if (argc != 2)
		return (0);

	t_data *data;
	data = init_data();
	
	get_map_len(argv, data);
	get_row_count(argv, data);
	get_col_count(argv, data);
	
	init_points(data);
	
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
	print_arr(data, 'c');

	//printf("%.1f, %.1f", data->points[2][7].x, data->points[2][7].y);
	free_point_arr(data);
	free(data);
}
