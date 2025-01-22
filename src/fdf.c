/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 10:47:40 by rhvidste          #+#    #+#             */
/*   Updated: 2025/01/22 18:05:50 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fdf.h"


t_data	*init_data()
{
	t_data	*data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->len = 0;
	data->rows = 0;
	data->cols = 0;
	data->points = NULL;
	return (data);
}

void	init_points(t_data *data)
{
	int	i;

	i = -1;
	data->points = malloc(sizeof(t_dp4 *) * data->rows);
	if (!data->points)
		ft_printf("point failure\n");
	while (++i < data->cols)
	{
		data->points[i] = malloc(sizeof(t_dp4) * data->cols);
		if (!data->points[i])
		{
			while (i--)
				free(data->points[i]);
			free(data->points);
			ft_printf("data points free'd");
			exit(1);
		}
	}
}

void	free_arr(t_dp4	**arr)
{
	int	 i;
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

int	main(int argc, char **argv)
{
	//int i;

	if (argc != 2)
		return (0);
	(void)argc;
	(void)argv;

	t_data *data;
	data = init_data();
	get_map_len(argv, data);
	get_row_count(argv, data);
	get_col_count(argv, data);
	init_points(data);
	//ft_printf("len = %d\nrows = %d\ncolumns = %d\n", data->len, data->rows, data->cols);
	
	//print_map(argv);

	/* how to assign 2d array of points----------------------------------------------
	t_dp4	**points;
	points = malloc(data->rows * sizeof(t_dp4 *));
	if (points == NULL)
		panic;
	i = -1;
	while (++i < data->cols)
	{
		points[i] = malloc(data->cols * sizeof(t_dp4));
		if (point[i] == NULL)
		{
			while (i--)
				free(points[i]);
			free(points);
			exit();
		}
	}
	//-------------------------------------------------------------------------------
	*/

	free_arr(data->points);
	free(data);
}

