/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 16:19:50 by rhvidste          #+#    #+#             */
/*   Updated: 2025/02/11 13:21:14 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Function to start mlx
void	mlx_start(t_data *data)
{
	mlx_set_setting(MLX_MAXIMIZED, true);
	if (!(data->mlx = mlx_init(WIDTH, HEIGHT, "FDF", true)))
		ft_error();
	mlx_get_monitor_size(0, &data->width, &data->height);
	data->img = mlx_new_image(data->mlx, data->width, data->height);
	if (!data->img || (mlx_image_to_window(data->mlx, data->img, 0, 0) < 0))
		ft_error();
}
