/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   orthographic_projection.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:30:40 by rhvidste          #+#    #+#             */
/*   Updated: 2025/02/06 16:06:52 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Function to init orthographic data
void	ortho_projection(t_data *data)
{
	t_matrix	orthographic;
	
	data->o->left = -50.0f;
	data->o->right = 50.0f;
	data->o->bottom = -50.0f;
	data->o->top = 50.0f;
	data->o->near = 0.1f;
	data->o->far = 100.0f;
	orthographic = create_orthographic_matrix(data->o);
//	multiply_projection_points(data, &orthographic);
	ortho_project(data, orthographic);
	data->flag = 'o';
}

// Function to init orthographic data
void	init_ortho_data(t_data *data)
{
	data->o = malloc(sizeof(t_ortho_data));
//	if (!data->o)
//	{
//		perror("Failed to allocate memory for ortho data");
//		exit(EXIT_FAILURE);
//	}
	ft_memset(data->o, 0, sizeof(t_ortho_data));
}

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

// Function to project into 2d space with orthographic projection. 
void	ortho_project(t_data *data, t_matrix orthographic)
{
	int		i;
	int		j;

	i = -1;
	while (++i < data->rows)
	{
		j = -1;
		while (++j < data->cols)
		{
			project_3d_to_2d(data->points[i][j], orthographic, &data->p2d[i][j]);
			//project_3d_to_2d(data->proj[i][j], orthographic, &data->p2d[i][j]);
		}
	}
}


