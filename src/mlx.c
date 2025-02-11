/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 16:19:50 by rhvidste          #+#    #+#             */
/*   Updated: 2025/02/11 13:16:49 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Function to start mlx
void	mlx_start(t_data *data)
{
	mlx_set_setting(MLX_MAXIMIZED, true);
	data->mlx = mlx_init(WIDTH, HEIGHT, "FDF", true);
	if (!data->mlx)
		ft_error();
	mlx_get_monitor_size(0, &data->width, &data->height);
	data->img = mlx_new_image(data->mlx, data->width, data->height);
	if (!data->img || (mlx_image_to_window(data->mlx, data->img, 0, 0) < 0))
		ft_error();
}

// Function keyhook for escaping the program
void	my_keyhook(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_RELEASE)
	{
		puts("Escape!");
		free(data->o);
		free_point_arr(data);
		free(data);
		exit(EXIT_SUCCESS);
	}
}
