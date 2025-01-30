/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2d_operations.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 14:09:56 by rhvidste          #+#    #+#             */
/*   Updated: 2025/01/30 12:49:48 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Function to scale in view Space based on max values / screen.
void	scale_view(t_data *data)
{
	double	scale_x;
	double	scale_y;
	int		i;
	int		j;

	scale_x = 0;
	scale_y = 0;
	scale_x = 0.1 * data->width / data->x_max;
	scale_y = 0.1 * data->height / data->y_max;
	printf("max x = %.2f\nmax y = %.2f\n", data->x_max, data->y_max);
	printf("scale x = %.2f\nscale y = %.2f", scale_x, scale_y);
	i = 0;
	while (i < data->rows)
	{
		j = 0;
		while (j < data->cols)
		{
			data->p2d[i][j].x *= scale_x;
			data->p2d[i][j].y *= scale_y;
			j++;
		}
		i++;
	}
}

// Function to center the projection in view space
void	offset_view(t_data *data)
{
	int	i;
	int	j;
	int	c_x;
	int	c_y;

	c_x = data->width / 2.0;
	c_y = data->height / 2.0;
	i = 0;
	while (i < data->rows)
	{
		j = 0;
		while (j < data->cols)
		{
			data->p2d[i][j].x += c_x;
			data->p2d[i][j].y += c_y;
			j++;
		}
		i++;
	}
}

// Function to center the projection to 0 in view space
void	center_view(t_data *data)
{
	int	i;
	int	j;
	int	c_x;
	int	c_y;

	c_x = data->width / 2.0;
	c_y = data->height / 2.0;
	i = 0;
	while (i < data->rows)
	{
		j = 0;
		while (j < data->cols)
		{
			data->p2d[i][j].x -= c_x;
			data->p2d[i][j].y -= c_y;
			j++;
		}
		i++;
	}
}

// Function tog the Max and Min values of view space 
void	get_max(t_data *data)
{
	int		i;
	int		j;

	i = 0;
	while (i < data->rows)
	{
		j = 0;
		while (j < data->cols)
		{
			if (data->p2d[i][j].x > data->x_max)
				data->x_max = data->p2d[i][j].x;
			if (data->p2d[i][j].y > data->y_max)
				data->y_max = data->p2d[i][j].y;
			j++;
		}
		i++;
	}
}
