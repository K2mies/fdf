/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d_operations.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 11:53:43 by rhvidste          #+#    #+#             */
/*   Updated: 2025/02/10 15:30:33 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Function to get the max 3D value to use as a offset
double	get_3D_max(t_data *data)
{
	int	i;
	int	j;

	double	max_x;
	double	max_y;
	double	max_z;

	max_x = data->points[0][0].x;
	max_y = data->points[0][0].y;
	max_z = data->points[0][0].z;

	i = -1;
	while (++i < data->rows)
	{
		j = -1;
		while (++j < data->cols)
		{
			if (max_x < data->points[i][j].x)
				max_x = data->points[i][j].x;
			if (max_y < data->points[i][j].y)
				max_y = data->points[i][j].y;		
			if (max_z < data->points[i][j].z)
				max_z = data->points[i][j].z;		
		}
	}
//	return(max_z);
//	return (max_x * max_y);
	return(max_x * max_y * max_z);
}
