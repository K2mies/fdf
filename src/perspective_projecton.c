/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perspective_projecton.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 14:53:31 by rhvidste          #+#    #+#             */
/*   Updated: 2025/02/07 17:30:21 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Function that contains the call to other perspective projection functions.

void	perspective_projection(t_data *d)
{
	t_matrix	perspective;
	t_matrix	translation; 
	double	trans_z;
	
//	trans_z = (get_3D_max(d) / 20.0f);
//	trans_z = 20.0f;
	trans_z = data->trans;
	printf("trans_z = %.1f\n", trans_z);

	printf("1: x = %.1f y = %.1f\n", d->points[0][0].x, d->points[0][0].y);
	translation = create_translation_matrix(0, 0, trans_z);
	multiply_points(d, &translation);
	printf("2: x = %.1f y = %.1f\n", d->points[0][0].x, d->points[0][0].y);

	d->p->fov = 60.0f;
	d->p->ar = (d->width / d->height);
	d->p->n = 0.1f;
	d->p->f = 100.0f;

	perspective = create_perspective_matrix(d->p->fov, d->p->ar, d->p->n, d->p->f);
//	multiply_points(d, &perspective);
	multiply_projection_points(d, &perspective);
	perspective_project(d, perspective);

	translation = create_translation_matrix(0, 0, -trans_z);
	multiply_points(d, &translation);
	printf("3: x = %.1f y = %.1f\n", d->points[0][0].x, d->points[0][0].y);
	d->flag = 'p';
}

// Function to init perpective data
void init_perspective_data(t_data *data)
{
	data->p = malloc(sizeof(t_perspective_data));
	ft_memset(data->p, 0, sizeof(t_perspective_data));
}

// Function to create a perspectrive matrix
t_matrix	create_perspective_matrix(double fov, double ar, double n, double f)
{	
	double		tan_half_fov;
	t_matrix	m;

//	(void)ar;
	m = create_empty_matrix();
//	//v2.0
//	double	scale = 1 / tan(fov * 0.5 * M_PI / 180);
//	m.m[0][0] = scale / ar;
//	m.m[1][1] = scale;
//	m.m[2][2] = -(f + n) / (f / n);
//	m.m[2][3] = -1;
//	m.m[3][2] = -2 * f * n / (f - n);
//	m.m[3][3] = 0;
//	return(m);

	//v1.0
	tan_half_fov = tan(fov * 0.5 * M_PI / 180.0);
	m.m[0][0] = 1.0f / (ar * tan_half_fov);
	m.m[1][1] = 1.0f / tan_half_fov;
	m.m[2][2] = (f + n) / (f - n);
	m.m[2][3] = -1.0f;
	m.m[3][2] = -2.0f * f * n / (f - n);
	m.m[3][3] = 0.0f;
	return (m);

//	//v3.0
//	double tf = 1.0 / tan(fov * 0.5 * M_PI / 180.0);
//
//	m.m[0][0] = tf / ar;
//	m.m[1][1] = tf;
//	m.m[2][2] = (f + n) / (n - f);
//	m.m[2][3] = -1.0;
//	m.m[3][2] = -(2.0 * f * n) /(f - n);
//	m.m[3][3] = 0.0;
//	return (m);
}

// Function to project into 2d view space with perspective projection.
void	perspective_project(t_data *data, t_matrix perspective)
{
	int		i;
	int		j;

	i = -1;
	while (++i < data->rows)
	{
		j = -1;
		while (++j < data->cols)
		{
//			perspective_project_3d_to_2d(data->points[i][j], perspective, &data->p2d[i][j]);
			perspective_project_3d_to_2d(data->proj[i][j], perspective, &data->p2d[i][j]);
		}
	}
}

// Function to projcet 3d perspective to 2d space
void	perspective_project_3d_to_2d(t_vec4 v, t_matrix m, t_vec2 *res)
{

//	//v3.0
//	t_vec4 projected = matrix_multiply_vector(m, v);
//	
//	if (projected.w != 0)
//	{
//		res->x = projected.x / projected.w;
//		res->y = projected.y / projected.w;
//	}
//	else
//	{
//		res->x = projected.x;
//		res->y = projected.y;
//	}
//
//	res->y = -res->y;

//	//v4.0
//	t_vec4 clip_coords;
//    clip_coords.x = m.m[0][0] * v.x + m.m[0][1] * v.y + m.m[0][2] * v.z + m.m[0][3] * v.w;
//    clip_coords.y = m.m[1][0] * v.x + m.m[1][1] * v.y + m.m[1][2] * v.z + m.m[1][3] * v.w;
//    clip_coords.z = m.m[2][0] * v.x + m.m[2][1] * v.y + m.m[2][2] * v.z + m.m[2][3] * v.w;
//    clip_coords.w = m.m[3][0] * v.x + m.m[3][1] * v.y + m.m[3][2] * v.z + m.m[3][3] * v.w;
//	
//	// Perspective divide
//    if (clip_coords.w != 0)
//    {
//        res->x = clip_coords.x / clip_coords.w;
//        res->y = clip_coords.y / clip_coords.w;
//    }
//    else
//    {
//        res->x = clip_coords.x;
//        res->y = clip_coords.y;
//    }

	//v1.0
	double	w;
		 w =  m.m[3][0] * v.x + m.m[3][1] * v.y + m.m[3][2] * v.z + m.m[3][3];
	res->x = (m.m[0][0] * v.x + m.m[0][1] * v.y + m.m[0][2] * v.z + m.m[0][3]) / w;
	res->y = (m.m[1][0] * v.x + m.m[1][1] * v.y + m.m[1][2] * v.z + m.m[1][3]) / w;
  	res->rgba = v.rgba;
	res->y = -res->y;
	res->x = -res->x;

}

