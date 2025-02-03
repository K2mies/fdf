/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_draw_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 16:31:10 by rhvidste          #+#    #+#             */
/*   Updated: 2025/02/03 16:37:28 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Function to clamp gradient values so they dont go out of bounds.
int clamp(int value, int min, int max)
{
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

// Function to caculate the line length for drawing
int calculate_pixel_length(int x1, int y1, int x2, int y2)
{
    int dx = x2 - x1;
    int dy = y2 - y1;
    return (int)sqrt(dx*dx + dy*dy);
}

// Function to check that line is drawn within bounds of the img buffer
int	is_valid(t_data *data, int x0, int y0, int x1, int y1)
{
	if (!((x0 > 0 && x0 < data->width) && (y0 > 0 && y0 < data->height)))
		return (0);
	if (!((x1 > 0 && x1 < data->width) && (y1 > 0 && y1 < data->height)))
		return (0);
	return (1);
}

