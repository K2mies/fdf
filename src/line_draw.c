/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rvidste@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 16:55:14 by rhvidste          #+#    #+#             */
/*   Updated: 2025/02/13 11:45:23 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Gradient refactoring using gdata
int	gradient(t_data *d, int start_color, int end_color)
{
	d->gd->start_r = extract_channel(start_color, 24);
	d->gd->start_g = extract_channel(start_color, 16);
	d->gd->start_b = extract_channel(start_color, 8);
	d->gd->end_r = extract_channel(end_color, 24);
	d->gd->end_g = extract_channel(end_color, 16);
	d->gd->end_b = extract_channel(end_color, 8);
	if (d->ld->len == 0)
		return (start_color);
	d->gd->start_r = d->gd->start_r
		+ (d->gd->end_r - d->gd->start_r)
		* d->ld->pix / d->ld->len;
	d->gd->start_g = d->gd->start_g
		+ (d->gd->end_g - d->gd->start_g)
		* d->ld->pix / d->ld->len;
	d->gd->start_b = d->gd->start_b
		+ (d->gd->end_b - d->gd->start_b)
		* d->ld->pix / d->ld->len;
	d->gd->start_r = clamp(d->gd->start_r, 0, 255);
	d->gd->start_g = clamp(d->gd->start_g, 0, 255);
	d->gd->start_b = clamp(d->gd->start_b, 0, 255);
	return ((d->gd->start_r << 24) | (d->gd->start_g << 16)
		| (d->gd->start_b << 8) | (d->gd->alpha));
}

// Function to get line data.
static void	put_line_data(t_data *data, t_vec2 p0, t_vec2 p1)
{
	data->ld->x0 = (int)p0.x;
	data->ld->y0 = (int)p0.y;
	data->ld->x1 = (int)p1.x;
	data->ld->y1 = (int)p1.y;
	data->ld->len = calculate_line_length(data->ld->x0, data->ld->y0,
			data->ld->x1, data->ld->y1);
	data->ld->pix = 0;
	data->ld->dx = abs(data->ld->x1 - data->ld->x0);
	if (data->ld->x0 < data->ld->x1)
		data->ld->sx = 1;
	else
		data->ld->sx = -1;
	data->ld->dy = -abs(data->ld->y1 - data->ld->y0);
	if (data->ld->y0 < data->ld->y1)
		data->ld->sy = 1;
	else
		data->ld->sy = -1;
	data->ld->err = data->ld->dx + data->ld->dy;
	data->ld->color = WHITE;
}

//Function to draw line to the screen.
void	draw_line(t_data *data, t_vec2 p0, t_vec2 p1)
{
	put_line_data(data, p0, p1);
	while (1)
	{
		draw_pixel(data, p0, p1);
		if (data->ld->x0 == data->ld->x1 && data->ld->y0 == data->ld->y1)
			break ;
		data->ld->e2 = 2 * data->ld->err;
		if (data->ld->e2 >= data->ld->dy)
		{
			data->ld->err += data->ld->dy;
			data->ld->x0 += data->ld->sx;
		}
		if (data->ld->e2 <= data->ld->dx)
		{
			data->ld->err += data->ld->dx;
			data->ld->y0 += data->ld->sy;
		}
		data->ld->pix++;
	}
}
