/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 10:47:40 by rhvidste          #+#    #+#             */
/*   Updated: 2025/02/13 12:58:46 by rhvidste         ###   ########.fr       */
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
	orthographic_rotation(data);
	ortho_projection(data);
	get_max_and_min(data);
	scale_view(data);
	offset_view(data);
	draw(data);
	mlx_key_hook(data->mlx, &my_keyhook, data);
	mlx_loop(data->mlx);
	mlx_delete_image(data->mlx, data->img);
	mlx_terminate(data->mlx);
	free_all(data, 'n');
	return (EXIT_SUCCESS);
}
