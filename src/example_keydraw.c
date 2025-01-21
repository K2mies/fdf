/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   example_keydraw.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 11:42:22 by rhvidste          #+#    #+#             */
/*   Updated: 2025/01/21 12:25:25 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdlib.h>
#include <stdio.h>
#include "MLX42/MLX42.h"

# define WIDTH 720
# define HEIGHT 480

# define RED   0xFF0000FF
# define GREEN 0x00FF00FF
# define BLUE  0x0000FFFF
# define BLACK 0x000000FF

static void	ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

void	my_keyhook(mlx_key_data_t keydata, void *param)
{
	static int	i = 0;
	static int	j = 0;
	//If we PRESS the J key draw on x.
	if (keydata.key == MLX_KEY_J && keydata.action == MLX_REPEAT)
	{
		i++;
		mlx_put_pixel(param, i, j, RED);
		puts("draw x");
		printf("%d\n", i);
	}
	//If we PRESS the K key draw on y.
	if (keydata.key == MLX_KEY_K && keydata.action == MLX_REPEAT)
	{
		j++;
		mlx_put_pixel(param, i, j, BLUE);
		puts("draw y");
		printf("%d\n", j);
	}
}

int32_t	main(void)
{
	mlx_set_setting(MLX_MAXIMIZED, true);
	mlx_t *mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);

	mlx_image_t *img = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
		ft_error();

	mlx_key_hook(mlx, &my_keyhook, img);
	mlx_loop(mlx);
	mlx_terminate(mlx);
}
