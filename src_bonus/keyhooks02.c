/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhooks02.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 10:47:55 by rhvidste          #+#    #+#             */
/*   Updated: 2025/02/11 15:27:39 by rhvidste         ###   ########.fr       */
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

// Function keyhook for zoom in and out
void	z_keyhook(double xdelta, double ydelta, void *param)
{
	t_data	*data;

	(void)xdelta;
	data = (t_data *)param;
	scroll_up(ydelta, data);
	scroll_down(ydelta, data);
}
