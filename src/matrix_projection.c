/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_projection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 13:18:31 by rhvidste          #+#    #+#             */
/*   Updated: 2025/02/05 15:47:01 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Function to create a orthographic perspective matrix
t_matrix	create_orthographic_matrix(t_ortho_data *o)
{
	t_matrix	m;

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

// Function to projcet 3d to 2d space
void	project_3d_to_2d(t_vec4 v, t_matrix m, t_vec2 *res)
{
	res->x = (m.m[0][0] * v.x + m.m[0][1] * v.y + m.m[0][2] * v.z + m.m[0][3]);
	res->y = (m.m[1][0] * v.x + m.m[1][1] * v.y + m.m[1][2] * v.z + m.m[1][3]);
	res->rgba = v.rgba;
}

// Function to apply matrix transformation to all 3d point vec4 vectors
void	multiply_points(t_data *data, t_matrix *matrix)
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
			data->points[i][j] = matrix_multiply_vector(*matrix,
				data->points[i][j]);
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
			project_3d_to_2d(data->points[i][j], orthographic,
				&data->p2d[i][j]);
			j++;
		}
		i++;
	}
}
