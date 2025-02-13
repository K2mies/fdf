/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_matrix_projection.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 13:18:31 by rhvidste          #+#    #+#             */
/*   Updated: 2025/02/12 14:44:32 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Function to apply matrix transformation to all 3d point vec4 vectors
void	multiply_points(t_data *data, t_matrix *matrix)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < data->rows)
	{
		j = 0;
		while (j < data->cols)
		{
			data->points[i][j] = matrix_multiply_vector(*matrix,
					data->points[i][j]);
			j++;
		}
		i++;
	}
}

// Function to apply matrix tranformations to copy of point array.
void	multiply_projection_points(t_data *data, t_matrix *matrix)
{
	int	i;
	int	j;

	copy_arr_data(data, data->proj, data->points);
	i = -1;
	while (++i < data->rows)
	{
		j = -1;
		while (++j < data->cols)
		{
			data->proj[i][j] = matrix_multiply_vector(*matrix,
					data->proj[i][j]);
		}
	}
}
