/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rvidste@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 16:55:14 by rhvidste          #+#    #+#             */
/*   Updated: 2025/01/27 10:18:52 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


void	draw_line(mlx_image_t *img, int x0, int y0, int x1, int y1, uint32_t color)
{
	int	dx;
	int	sx;
	int	dy;
	int	sy;
	int	err;
	int	e2;

	dx = abs(x1 - x0);
	sx = x0 < x1 ? 1 : -1;
	dy = -abs(y1 - y0);
	sy = y0 < y1 ? 1 : -1;
	err = dx + dy;

	while (1)
	{
		mlx_put_pixel(img, x0, y0, color);
		if (x0 == x1 && y0 == y1)
			break;
		e2 = 2 * err;
		if (e2 >= dy)
		{
			err += dy;
			x0 += sx;
		}
		if (e2 <= dx)
		{
			err += dx;
			y0 += sy;
		}
	}
}
