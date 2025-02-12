/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 10:18:08 by rhvidste          #+#    #+#             */
/*   Updated: 2025/02/12 17:06:33 by rhvidste         ###   ########.fr       */
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
void	free_point_arr(t_data *data, char flag)
{
	int		i;

	i = -1;
	while (++i < data->rows)
	{
		if (flag == 'a')
			free(data->points[i]);
		if (flag == 'b')
			free(data->proj[i]);
		if (flag == 'c')
			free(data->p2d[i]);
	}
	if (flag == 'a')
		free(data->points);
	if (flag == 'b')
		free(data->proj);
	if (flag == 'c')
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
void	free_all(t_data *data, char flag)
{
	if (data->o)
		free(data->o);
	if (data->p)
		free(data->p);
	if (data->ld)
		free(data->ld);
	if (data->gd)
		free(data->gd);
	if (data->points)
		free_point_arr(data, 'a');
	if (data->proj)
		free_point_arr(data, 'b');
	if (data->p2d)
		free_point_arr(data, 'c');
	free(data);
	if (flag == 'f')
		exit(EXIT_FAILURE);
	if (flag == 's')
		exit(EXIT_SUCCESS);
}
