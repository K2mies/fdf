/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhooks01.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 11:22:59 by rhvidste          #+#    #+#             */
/*   Updated: 2025/02/12 13:32:38 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Function keyhook for rotation transformations.
void	r_keyhook(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_Q))
		rotate(data, 5, 0, 0);
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
		rotate(data, 0, 5, 0);
	if (mlx_is_key_down(data->mlx, MLX_KEY_E))
		rotate(data, 0, 0, 5);
}

// Function to handle z depth translation
void	tz_keyhook(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_EQUAL))
	{
		data->trans_z += 10.0f;
		project(data);
		redraw(data);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_MINUS))
	{
		data->trans_z -= 10.0f;
		project(data);
		redraw(data);
	}
}

// Function to handle x viewspace translations
void	tx_keyhook(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
	{
		data->trans_x -= 10.0f;
		project(data);
		redraw(data);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
	{
		data->trans_x += 10.0f;
		project(data);
		redraw(data);
	}
}

// Function to handle y viewspace translations
void	ty_keyhook(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_UP))
	{
		data->trans_y -= 10.0f;
		project(data);
		redraw(data);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_DOWN))
	{
		data->trans_y += 10.0f;
		project(data);
		redraw(data);
	}
}

// Function to reset the projecrtion and reparse the data
void	reset_keyhook(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_R))
	{
		parse_points(data->argv, data);
		data->trans_z = 150.00f + (get_3d_max(data) / 10.0f);
		project(data);
		get_max_and_min(data);
		data->trans_x = 0;
		data->trans_y = 0;
		data->zoom = 0.0;
		redraw(data);
	}
}
