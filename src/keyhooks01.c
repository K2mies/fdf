/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhooks01.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 11:22:59 by rhvidste          #+#    #+#             */
/*   Updated: 2025/02/07 17:30:17 by rhvidste         ###   ########.fr       */
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
//			t_matrix	translation;
//			color_fill(data);
//			double	trans_z = (get_3D_max(data) / 20.0f);
//			translation = create_translation_matrix(0, 0, trans_z);
//			translation = create_translation_matrix(0, 0, (get_3D_max(data) / 20.0f));
//			multiply_points(data, &translation);
//			data->trans = get_3D_max(data) / 20.0f;
			data->trans = data->x_max * 2;
			perspective_projection(data);
//			center_view(data);
//			get_max_and_min(data);
//			center_view(data);
//			scale_view(data);
//			offset_view(data);
//			draw(data);
			//Reseting the 3d translation here so that it does not effect other operations.
//			translation = create_translation_matrix(0, 0, -trans_z);
//			multiply_points(data, &translation);
//			center_view(data);
//			data->flag = 'p';	
			ft_printf("Projection set to: perspective\n");	
		}
		else if (data->flag == 'p')
		{
//			t_matrix	translation;
//			color_fill(data);
//			translation = create_translation_matrix(0, 0, -(get_3D_max(data) / 20.0f));
//			multiply_points(data, &translation);
			ortho_projection(data);
//			center_view(data);
//			get_max_and_min(data);
//			scale_view(data);
//			scale_view(data);
//			offset_view(data);
//			draw(data);

//			data->flag = 'o';
			ft_printf("Projection set to: orthographic\n");
			
		}
		color_fill(data);
		get_max_and_min(data);
		scale_view(data);
		offset_view(data);
		draw(data);
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
		color_fill(data);
//		get_max_and_min(data);
		scale_view(data);
		offset_view(data);
		draw(data);
//		center_view(data);
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
		color_fill(data);
//		get_max_and_min(data);
		scale_view(data);
		offset_view(data);
		draw(data);
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
		color_fill(data);
//		get_max_and_min(data);
		scale_view(data);
		offset_view(data);
		draw(data);
	}
}
