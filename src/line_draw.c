/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rvidste@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 16:55:14 by rhvidste          #+#    #+#             */
/*   Updated: 2025/01/28 16:19:11 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_line(t_data *data, int x0, int y0, int x1, int y1, uint32_t color)
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
		mlx_put_pixel(data->img, x0, y0, color);
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

//refactored code for norminette ristrictions.
/*
void	init_line_data(t_line_data *ld, int x0, int y0, int x1, int y1);
void	update_coordinates(t_line_data *ld, int *x0, int *y0);

void	draw_line(t_data *data, int x0, int y0, int x1, int y1)
{
    t_line_data ld;
    int e2;

    init_line_data(&ld, x0, y0, x1, y1);
    while (1)
    {
        mlx_put_pixel(data->img, x0, y0, data->color);
        if (x0 == x1 && y0 == y1)
            break;
        e2 = 2 * ld.err;
        update_coordinates(&ld, &x0, &y0);
    }
}

void	init_line_data(t_line_data *ld, int x0, int y0, int x1, int y1)
{
    ld->dx = abs(x1 - x0);
    ld->dy = -abs(y1 - y0);
    if (x0 < x1)
        ld->sx = 1;
    else
        ld->sx = -1;
    if (y0 < y1)
        ld->sy = 1;
    else
        ld->sy = -1;
    ld->err = ld->dx + ld->dy;
}

void	update_coordinates(t_line_data *ld, int *x0, int *y0)
{
    if (2 * ld->err >= ld->dy)
    {
        ld->err += ld->dy;
        *x0 += ld->sx;
    }
    if (2 * ld->err <= ld->dx)
    {
        ld->err += ld->dx;
        *y0 += ld->sy;
    }
}
*/
