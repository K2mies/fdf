/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:42:07 by rhvidste          #+#    #+#             */
/*   Updated: 2025/02/10 15:36:39 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Master Function to init all data
t_data	*init_all(int argc, char **argv)
{
	if(!(validate_map(argc, argv)))
	{
		ft_printf("map is invalid\n");
		exit(EXIT_FAILURE);
	}
	t_data	*data;
	data = init_data();
	get_map_len(argv, data);
	get_row_count(argv, data);
	get_col_count(argv, data);
	init_3d_points(data);
	init_proj_points(data);
	init_2d_points(data);
	memset_points(data);
	init_ortho_data(data);
	init_perspective_data(data);
	init_line_data(data);
	init_gradient_data(data);
	data->argv = argv;
	data->argc = argc;
	return (data);
}

// Function to initialize global data
t_data	*init_data(void)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
	{
		perror("Failed to allocate memory for data");
		exit(EXIT_FAILURE);
	}
	ft_memset(data, 0, sizeof(t_data));
	return (data);
}

// Function to init line data
void	init_line_data(t_data *data)
{
	data->ld = malloc(sizeof(t_line_data));
	if (!data->ld)
	{
		perror("Failed to allocate memory for line data");
		exit(EXIT_FAILURE);
	}
	ft_memset(data->ld, 0, sizeof(t_line_data));
	data->ld->color = WHITE;
}

// Function to init gradient data
void	init_gradient_data(t_data *data)
{
	data->gd = malloc(sizeof(t_gradient_data));
//	if (!data->o)
//	{
//		perror("Failed to allocate memory for gradient data");
//		exit(EXIT_FAILURE);
//	}
	ft_memset(data->gd, 0, sizeof(t_gradient_data));
	data->gd->alpha = 255;
}
