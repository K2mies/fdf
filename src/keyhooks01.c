/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhooks01.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 11:22:59 by rhvidste          #+#    #+#             */
/*   Updated: 2025/02/10 17:22:47 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// ESC Keyhook to exit the program
void	esc_keyhook(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
}


// Function keyhook for changing the perspective
void	p_keyhook(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_P))
	{
		if (data->flag == 'o')
		{
			perspective_projection(data);
			ft_printf("Projection set to: perspective\n");	
		}
		else if (data->flag == 'p')
		{
			ortho_projection(data);
			ft_printf("Projection set to: orthographic\n");
			
		}
		get_max_and_min(data);
		redraw(data);
	}
}

// Function keyhook for rotation transformations.
void	r_keyhook(void *param)
{
	t_data	*data;
	
	data = (t_data *)param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_Q))
	{
		t_matrix	rot_x;
		rot_x = create_rotation_x_matrix(deg_to_rad(5));
		multiply_points(data, &rot_x);
		if (data->flag == 'o')
			ortho_projection(data);
		else
			perspective_projection(data);
		redraw(data);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
	{
		t_matrix	rot_y;
		rot_y = create_rotation_y_matrix(deg_to_rad(5));
		multiply_points(data, &rot_y);
		if (data->flag == 'o')
			ortho_projection(data);
		else
			perspective_projection(data);
		redraw(data);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_E))
	{
		t_matrix	rot_z;
		rot_z = create_rotation_z_matrix(deg_to_rad(5));
		multiply_points(data, &rot_z);
		if (data->flag == 'o')
			ortho_projection(data);
		else
			perspective_projection(data);
		redraw(data);
	}
}

// Function keyhook for zoom in and out

void	z_keyhook(double xdelta, double ydelta, void *param)
{
	t_data	*data;

	(void)xdelta;
	data = (t_data *)param;

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

void	t_keyhook(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_EQUAL))
	{
		data->trans_z += 10.0f;
		if (data->flag == 'o')
			ortho_projection(data);
		else
			perspective_projection(data);
		redraw(data);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_MINUS))
	{
		data->trans_z -= 10.0f;
		if (data->flag == 'o')
			ortho_projection(data);
		else
			perspective_projection(data);
		redraw(data);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_UP))
	{
		data->trans_y -= 10.0f;
		if (data->flag == 'o')
			ortho_projection(data);
		else
			perspective_projection(data);
		redraw(data);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_DOWN))
	{
		data->trans_y += 10.0f;
		if (data->flag == 'o')
			ortho_projection(data);
		else
			perspective_projection(data);
		redraw(data);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
	{
		data->trans_x -= 10.0f;
		if (data->flag == 'o')
			ortho_projection(data);
		else
			perspective_projection(data);
		redraw(data);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
	{
		data->trans_x += 10.0f;
		if (data->flag == 'o')
			ortho_projection(data);
		else
			perspective_projection(data);
		redraw(data);
	}
}

void	reset_keyhook(void *param)
{
	t_data *data;

	data = (t_data *)param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_R))
	{
		parse_points(data->argv, data);
		data->trans_z = 150.00f + (get_3D_max(data) / 10.0f);
		if (data->flag == 'o')
			ortho_projection(data);
		else
			perspective_projection(data);
		get_max_and_min(data);
		data->trans_x = 0;
		data->trans_y = 0;
		data->zoom = 0.0;
		redraw(data);
	}
}
