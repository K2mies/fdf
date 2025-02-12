/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhook_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 11:12:50 by rhvidste          #+#    #+#             */
/*   Updated: 2025/02/11 15:26:06 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Function to handle scroll up
void	scroll_up(double ydelta, t_data *data)
{
	if (ydelta > 0)
	{
		if (data->flag == 'o')
		{
			data->zoom += 100.0f;
			ortho_projection(data);
		}
		else
		{
			data->zoom += 100.0f;
			perspective_projection(data);
		}
		redraw(data);
	}
}

// Function to handle scroll down
void	scroll_down(double ydelta, t_data *data)
{
	if (ydelta < 0)
	{
		if (data->flag == 'o')
		{
			data->zoom -= 100.0f;
			ortho_projection(data);
		}
		else
		{
			data->zoom -= 100.f;
			perspective_projection(data);
		}
		redraw(data);
	}
}

//Function to handle rotation
void	rotate(t_data *data, double x, double y, double z)
{
	t_matrix	rot_x;
	t_matrix	rot_y;
	t_matrix	rot_z;

	rot_x = create_rotation_x_matrix(deg_to_rad(x));
	rot_y = create_rotation_y_matrix(deg_to_rad(y));
	rot_z = create_rotation_z_matrix(deg_to_rad(z));
	multiply_points(data, &rot_x);
	multiply_points(data, &rot_y);
	multiply_points(data, &rot_z);
	project(data);
	redraw(data);
}
