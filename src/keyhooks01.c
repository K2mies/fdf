/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhooks01.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 11:22:59 by rhvidste          #+#    #+#             */
/*   Updated: 2025/02/06 15:01:37 by rhvidste         ###   ########.fr       */
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
			t_matrix	translation;
			color_fill(data);
			double	trans_z = (get_3D_max(data) / 20.0f);
			translation = create_translation_matrix(0, 0, trans_z);
//			translation = create_translation_matrix(0, 0, (get_3D_max(data) / 20.0f));
			multiply_points(data, &translation);
			perspective_projection(data);
//			center_view(data);
			get_max_and_min(data);
//			center_view(data);
			scale_view(data);
			offset_view(data);
			draw(data);	
			translation = create_translation_matrix(0, 0, -trans_z);
			multiply_points(data, &translation);
			center_view(data);
//			data->flag = 'p';	
			ft_printf("Projection set to: perspective\n");	
		}
		else if (data->flag == 'p')
		{
//			t_matrix	translation;
			color_fill(data);
//			translation = create_translation_matrix(0, 0, -(get_3D_max(data) / 20.0f));
//			multiply_points(data, &translation);
			ortho_projection(data);
//			center_view(data);
			get_max_and_min(data);
			scale_view(data);
			scale_view(data);
			offset_view(data);
			draw(data);

//			data->flag = 'o';
			ft_printf("Projection set to: orthographic\n");
			
		}
	}
}


