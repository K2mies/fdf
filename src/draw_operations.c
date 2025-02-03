/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 14:11:33 by rhvidste          #+#    #+#             */
/*   Updated: 2025/02/03 10:31:38 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Function to fill the background with black useing put_pixel()
void	color_fill(t_data *data)
{
	uint32_t	i;
	uint32_t	j;

	i = 0;
	j = 0;
	while (i < data->img->width)
	{
		j = 0;
		while (j < data->img->height)
		{
			mlx_put_pixel(data->img, i, j, BLACK);
			j++;
		}
		i++;
	}
}

// Function to draw the whole grid
void	draw(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->rows)
	{
		j = 0;
		while (j < data->cols)
		{
			if (i < data->rows - 1)
				draw_line(data, data->p2d[i][j], data->p2d[i + 1][j]);
			if (j < data->cols - 1)
				draw_line(data, data->p2d[i][j],data->p2d[i][j + 1]);
			j++;
		}
		i++;
	}
}


//// Function to draw the whole grid
//void	draw(t_data *data)
//{
//	int	i;
//	int	j;
//
//	i = 0;
//	while (i < data->rows)
//	{
//		j = 0;
//		while (j < data->cols)
//		{
//			if (i < data->rows - 1)
//				draw_line(data, (int)data->p2d[i][j].x, (int)data->p2d[i][j].y,
//					(int)data->p2d[i + 1][j].x, (int)data->p2d[i + 1][j].y, WHITE);
//			if (j < data->cols - 1)
//				draw_line(data, (int)data->p2d[i][j].x, (int)data->p2d[i][j].y,
//					(int)data->p2d[i][j + 1].x, (int)data->p2d[i][j + 1].y, WHITE);
//			j++;
//		}
//		i++;
//	}
//}
