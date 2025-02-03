/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_projection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 13:18:31 by rhvidste          #+#    #+#             */
/*   Updated: 2025/01/31 18:04:39 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Function to create a orthographic perspective matrix
t_matrix	create_orthographic_matrix(t_ortho_data *o)
{
	t_matrix	m;

	//m = {{{0}}};
	m = create_empty_matrix();
	m.m[0][0] = 2.0f / (o->right - o->left);
	m.m[1][1] = 2.0f / (o->top - o->bottom);
	m.m[2][2] = -2.0f / (o->far - o->near);
	m.m[3][0] = -(o->right + o->left) / (o->right - o->left);
	m.m[3][1] = -(o->top + o->bottom) / (o->top - o->bottom);
	m.m[3][2] = -(o->far + o->near) / (o->far - o->near);
	m.m[3][3] = 1.0f;
	return (m);
}

// Function to create a perspective matrix for projection.
//									  fov        |aspect r | near     |far     |
t_matrix	create_perspective_matrix(double fov, double ar, double n, double f)
{	
	double		tan_half_fov;
	t_matrix	m;

	//m = {{{0}}};
	m = create_empty_matrix();
	tan_half_fov = tan(fov * 0.5 * M_PI / 180.0);
	m.m[0][0] = 1.0f / (ar * tan_half_fov);
	m.m[1][1] = 1.0f / tan_half_fov;
	m.m[2][2] = (f + n) / (f - n);
	m.m[2][3] = -2.0f * f * n / (f - n);
	m.m[3][2] = -1.0f;
	return (m);
}

// Function to projcet 3d to 2d space
void	project_3d_to_2d(t_vec4 v, t_matrix m, t_vec2 *res)
{
	//double	w;

	//	 w =  m.m[3][0] * v.x + m.m[3][1] * v.y + m.m[3][2] * v.z + m.m[3][3];
	//res->x = (m.m[0][0] * v.x + m.m[0][1] * v.y + m.m[0][2] * v.z + m.m[0][3]) / w;
	//res->y = (m.m[1][0] * v.x + m.m[1][1] * v.y + m.m[1][2] * v.z + m.m[1][3]) / w;
	res->x = (m.m[0][0] * v.x + m.m[0][1] * v.y + m.m[0][2] * v.z + m.m[0][3]);
	res->y = (m.m[1][0] * v.x + m.m[1][1] * v.y + m.m[1][2] * v.z + m.m[1][3]);
	res->rgba = v.rgba;
	//res->x = (res->x + 1) * 0.5 * WIDTH;
	//res->y = (1 - res->y) * 0.5 * HEIGHT;
	//res->x *= 100;
	//res->y *= 100;
}


// Function to apply matrix transformation to all 3d point vec4 vectors
void multiply_points(t_data *data, t_matrix *matrix)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < data->rows)
	{
		j = 0;
		while(j < data->cols)
		{
			data->points[i][j] = matrix_multiply_vector(*matrix, data->points[i][j]);
			j++;
		}
		i++;
	}
}

// Function to project into 2d space with orthographic projection. 
void	ortho_project(t_data *data, t_matrix orthographic)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < data->rows)
	{
		j = 0;
		while (j < data->cols)
		{
			project_3d_to_2d(data->points[i][j], orthographic, &data->p2d[i][j]);
			j++;
		}
		i++;
	}
}
