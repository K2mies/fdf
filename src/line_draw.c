/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rvidste@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 16:55:14 by rhvidste          #+#    #+#             */
/*   Updated: 2025/01/31 15:06:17 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#define R(a) (((a) >> 24) & 0xFF)
#define G(a) (((a) >> 16) & 0xFF)
#define B(a) (((a) >> 8) & 0xFF)
#define RGB(r, g, b) (((r) << 24) | ((g) >> 16) | ((b) >> 8))

//int	gradient(int startcolor, int endcolor, int len, int pix)
//{
//	double increment[3];
//	int	new[3];
//	int	newcolor;
//
//	increment[0] = (double)((R(endcolor))) - (R(startcolor)) / (double)len;
//	increment[1] = (double)((G(endcolor))) - (G(startcolor)) / (double)len;
//	increment[2] = (double)((B(endcolor))) - (B(startcolor)) / (double)len;
//
//	new[0] = (R(startcolor)) + (int)(pix * increment[0]);
//	new[1] = (G(startcolor)) + (int)(pix * increment[1]);
//	new[2] = (B(startcolor)) + (int)(pix * increment[2]);
//
//	newcolor = RGB(new[0], new[1], new[2]);
//
//	return (newcolor);
//}

int clamp(int value, int min, int max)
{
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

int gradient(int startcolor, int endcolor, int len, int pix)
{
    if (len == 0)
        return startcolor;

    int start_r = R(startcolor), start_g = G(startcolor), start_b = B(startcolor);
    int end_r = R(endcolor), end_g = G(endcolor), end_b = B(endcolor);

//    printf("Start color: 0x%08X (R:%d, G:%d, B:%d)\n", startcolor, start_r, start_g, start_b);
//    printf("End color: 0x%08X (R:%d, G:%d, B:%d)\n", endcolor, end_r, end_g, end_b);

    double r = start_r + (end_r - start_r) * (double)pix / len;
    double g = start_g + (end_g - start_g) * (double)pix / len;
    double b = start_b + (end_b - start_b) * (double)pix / len;

//	ft_printf("pix / len = %d\n", pix / len);
//	(void)pix;
//    double r = start_r + (end_r - start_r) * (double)0.3;
//    double g = start_g + (end_g - start_g) * (double)0.3;
//    double b = start_b + (end_b - start_b) * (double)0.3;

    int result_r = clamp((int)r, 0, 255);
    int result_g = clamp((int)g, 0, 255);
    int result_b = clamp((int)b, 0, 255);

    int result = (result_r << 24) + (result_g << 16) + (result_b << 8) + (255);
//  printf("Gradient result: 0x%08X (R:%d, G:%d, B:%d)\n", result, result_r, result_g, result_b);

    return result;
}

//int gradient(int startcolor, int endcolor, int len, int pix)
//{
//	if (len == 0)
//		return startcolor;
//    //double r = R(startcolor) + (R(endcolor) - R(startcolor)) * (double)pix / len;
//    //double g = G(startcolor) + (G(endcolor) - G(startcolor)) * (double)pix / len;
//    //double b = B(startcolor) + (B(endcolor) - B(startcolor)) * (double)pix / len;
//	double r = (double)(R(startcolor)) + ((double)(R(endcolor)) - (double)(R(startcolor))) * (double)pix / len;
//	double g = (double)(G(startcolor)) + ((double)(G(endcolor)) - (double)(G(startcolor))) * (double)pix / len;
//	double b = (double)(B(startcolor)) + ((double)(B(endcolor)) - (double)(B(startcolor))) * (double)pix / len;
//	
//	int start_r = R(startcolor), start_g = G(startcolor), start_b = B(startcolor);
//	int end_r = R(endcolor), end_g = G(endcolor), end_b = B(endcolor);
//
//	printf("Start color: %06X (R:%d, G:%d, B:%d)\n", startcolor, start_r, start_g, start_b);
//	printf("End color: %06X (R:%d, G:%d, B:%d)\n", endcolor, end_r, end_g, end_b);
//    // Clamp values to ensure valid RGB range
//    r = clamp((int)r, 0, 255);
//    g = clamp((int)g, 0, 255);
//    b = clamp((int)b, 0, 255);
//
////	printf("Gradient: pix=%d len=%d r=%f g=%f b=%f\n", pix, len, r, g, b);
////	int result = RGBA((int)r, (int)g, (int)b, 255);
////	int	result = RGB((int)r, (int)g, (int)b);
//	int result = (result_r << 16) | (result_g << 8) | result_b;
//	printf("Gradient result: 0x%08X (R:%d, G:%d, B:%d)\n", result, result_r, result_g, result_b);
////	printf("Gradient result: %06X (R:%d, G:%d, B:%d)\n", result, (int)r, (int)g, (int)b); 
//
//	return (result);
////	return RGB((int)r, (int)g, (int)b);
////	return RGBA((int)r, (int)g, (int)b, 255);
////	return RGB((int)r, (int)g, (int)b);
//}

 
int calculate_pixel_length(int x1, int y1, int x2, int y2)
{
    int dx = x2 - x1;
    int dy = y2 - y1;
    return (int)sqrt(dx*dx + dy*dy);
}


static	int	is_valid(t_data *data, int x0, int y0, int x1, int y1)
{
	if (!((x0 > 0 && x0 < data->width) && (y0 > 0 && y0 < data->height)))
		return (0);
	if (!((x1 > 0 && x1 < data->width) && (y1 > 0 && y1 < data->height)))
		return (0);
	return (1);
}

//void	draw_line(t_data *data, int x0, int y0, int x1, int y1, uint32_t color)
void	draw_line(t_data *data, t_vec2 p0, t_vec2 p1)
{
	int	dx;
	int	sx;
	int	dy;
	int	sy;
	int	err;
	int	e2;

	int	x0 = (int)p0.x;
	int	y0 = (int)p0.y;
	int	x1 = (int)p1.x;
	int	y1 = (int)p1.y;

	int len;
	int	pix;

	len = calculate_pixel_length(x0, y0, x1, y1);
	pix = 0;	

	dx = abs(x1 - x0);
	sx = x0 < x1 ? 1 : -1;
	dy = -abs(y1 - y0);
	sy = y0 < y1 ? 1 : -1;
	err = dx + dy;

	unsigned int color;
	color = WHITE;

	while (1)
	{
		if (is_valid(data, x0, y0, x1, y1))
		{
			color = gradient(p0.rgba, p1.rgba, len, pix);
			mlx_put_pixel(data->img, x0, y0, color);
			//mlx_put_pixel(data->img, x0, y0, p0.rgba);//this is printing correct colors
			//mlx_put_pixel(data->img, x0, y0, 0xFFFF);
			//mlx_put_pixel(data->img, x0, y0, color);
			//mlx_put_pixel(data->img, x0, y0, 255 << 8 | 0xff);
			//mlx_put_pixel(data->img, x0, y0, 65535);
		}
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
		pix++;
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
