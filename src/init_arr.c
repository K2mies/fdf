/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_arr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 11:14:54 by rhvidste          #+#    #+#             */
/*   Updated: 2025/02/12 17:22:47 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Function to init 3d point array
void	init_3d_points(t_data *data)
{
	int	i;

	i = -1;
	data->points = malloc(sizeof(t_vec4 *) * data->rows);
	if (!data->points)
		ft_printf("point failure\n");
	while (++i < data->rows)
	{
		data->points[i] = calloc(data->cols, sizeof(t_vec4));
		if (!data->points[i])
		{
			while (i--)
				free(data->points[i]);
			free(data->points);
			ft_printf("data points free'd");
			free_all(data, 'f');
			exit(1);
		}
	}
}

// Function to init 2d point array
void	init_2d_points(t_data *data)
{
	int	i;

	i = -1;
	data->p2d = malloc(sizeof(t_vec2 *) * data->rows);
	if (!data->p2d)
		ft_printf("point failure\n");
	while (++i < data->rows)
	{
		data->p2d[i] = calloc(data->cols, sizeof(t_vec2));
		if (!data->p2d[i])
		{
			while (i--)
				free(data->p2d[i]);
			free(data->p2d);
			ft_printf("data points free'd");
			free_all(data, 'f');
			exit(1);
		}
	}
}

// Function to initialise 3dpoint data w and rgba value.
void	memset_points(t_data *data)
{
	int		i;
	int		j;

	i = -1;
	while (++i < data->rows)
	{
		j = -1;
		while (++j < data->cols)
		{
			data->points[i][j].x = 0;
			data->points[i][j].y = 0;
			data->points[i][j].z = 0;
			data->points[i][j].w = 1;
			data->points[i][j].rgba = ft_atoi_base("0xFFFFFFFF", 16);
		}
	}
}
