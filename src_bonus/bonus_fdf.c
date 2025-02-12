/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_fdf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 10:47:40 by rhvidste          #+#    #+#             */
/*   Updated: 2025/02/12 17:08:26 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fdf.h"

int32_t	main(int argc, char **argv)
{
	t_data	*data;

	data = init_all(argc, argv);
	parse_points(argv, data);
	mlx_start(data);
	color_fill(data);
	ortho_projection(data);
	get_max_and_min(data);
	data->trans_z = 150.00f + (get_3d_max(data) / 30.0f);
	scale_view(data);
	offset_view(data);
	draw(data);
	mlx_loop_hook(data->mlx, &esc_keyhook, data);
	mlx_loop_hook(data->mlx, &p_keyhook, data);
	mlx_loop_hook(data->mlx, &r_keyhook, data);
	mlx_loop_hook(data->mlx, &tz_keyhook, data);
	mlx_loop_hook(data->mlx, &tx_keyhook, data);
	mlx_loop_hook(data->mlx, &ty_keyhook, data);
	mlx_loop_hook(data->mlx, &reset_keyhook, data);
	mlx_scroll_hook(data->mlx, &z_keyhook, data);
	mlx_loop(data->mlx);
	mlx_delete_image(data->mlx, data->img);
	free_all(data, 'n');
	mlx_terminate(data->mlx);
	return (EXIT_SUCCESS);
}
