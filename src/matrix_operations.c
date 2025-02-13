/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 13:13:45 by rhvidste          #+#    #+#             */
/*   Updated: 2025/02/13 11:59:04 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Function to create an empty matrix
t_matrix	create_empty_matrix(void)
{
	t_matrix	matrix;

	matrix = (t_matrix)
	{{
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0}
	}};
	return (matrix);
}

// Function to create an identity matrix
t_matrix	create_identity_matrix(void)
{
	t_matrix	matrix;

	matrix = (t_matrix)
	{{
	{1, 0, 0, 0},
	{0, 1, 0, 0},
	{0, 0, 1, 0},
	{0, 0, 0, 1}
	}};
	return (matrix);
}

// Function to multiply a matrix by a vector.
t_vec4	matrix_multiply_vector(t_matrix m, t_vec4 v)
{
	t_vec4	res;

	res.x = m.m[0][0] * v.x + m.m[0][1] * v.y + m.m[0][2] * v.z + m.m[0][3];
	res.y = m.m[1][0] * v.x + m.m[1][1] * v.y + m.m[1][2] * v.z + m.m[1][3];
	res.z = m.m[2][0] * v.x + m.m[2][1] * v.y + m.m[2][2] * v.z + m.m[2][3];
	res.w = m.m[3][0] * v.x + m.m[3][1] * v.y + m.m[3][2] * v.z + m.m[3][3];
	if (res.w != 1 && res.w != 0)
	{
		res.x /= res.w;
		res.y /= res.w;
		res.z /= res.w;
	}
	res.rgba = v.rgba;
	return (res);
}
