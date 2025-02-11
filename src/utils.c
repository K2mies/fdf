/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 10:18:08 by rhvidste          #+#    #+#             */
/*   Updated: 2025/02/11 14:46:05 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Function to free array
void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

// Function to free 3d point array.
void	free_point_arr(t_data *data)
{
	int		i;

	i = -1;
	while (++i < data->rows)
	{
		free(data->points[i]);
		free(data->proj[i]);
		free(data->p2d[i]);
	}
	free(data->points);
	free(data->proj);
	free(data->p2d);
}

// Function to convert from degrees to radians
double	deg_to_rad(double degrees)
{
	return (degrees * (M_PI / 180.0));
}

// Function to get the len of an array
int	arr_len(char **arr)
{
	int		i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

// Function to free all data
void	free_all(t_data *data)
{
	free(data->o);
	free(data->p);
	free(data->ld);
	free(data->gd);
	free_point_arr(data);
	free(data);
}
