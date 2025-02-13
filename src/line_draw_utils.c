/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_draw_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 16:31:10 by rhvidste          #+#    #+#             */
/*   Updated: 2025/02/13 11:33:34 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Function to clamp gradient values so they dont go out of bounds
int	clamp(int value, int min, int max)
{
	if (value < min)
		return (min);
	if (value > max)
		return (max);
	return (value);
}

// Function to caculate the line length for drawing
int	calculate_line_length(int x1, int y1, int x2, int y2)
{
	int	dx;
	int	dy;

	dx = x2 - x1;
	dy = y2 - y1;
	return ((int)sqrt(dx * dx + dy * dy));
}

// Function to check that line is drawn within bounds of the img buffer
int	is_valid_line(t_data *data)
{
	int	x0;
	int	y0;
	int	x1;
	int	y1;

	x0 = data->ld->x0;
	y0 = data->ld->y0;
	x1 = data->ld->x1;
	y1 = data->ld->y1;
	if ((x0 > data->width && x1 > data->width) || (x0 < 0 && x1 < 0))
		return (0);
	if ((y0 > data->height && y1 > data->height) || (y0 < 0 && y1 < 0))
		return (0);
	return (1);
}

// Function to check if pixel is valid to draw
int	is_valid_pixel(t_data *data)
{
	int	x0;
	int	y0;

	x0 = data->ld->x0;
	y0 = data->ld->y0;
	if (((x0 > 0 && x0 < data->width) && (y0 > 0 && y0 < data->height)))
		return (1);
	return (0);
}

// Function to extract the color channel
int	extract_channel(int color, int shift)
{
	return ((color >> shift) & 0xFF);
}
