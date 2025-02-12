/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_matrix_transforms.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 12:36:55 by rhvidste          #+#    #+#             */
/*   Updated: 2025/02/12 14:44:42 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Function to create a scaling matrix
t_matrix	create_scaling_matrix(double sx, double sy, double sz)
{
	t_matrix	m;

	m = create_identity_matrix();
	m.m[0][0] = sx;
	m.m[1][1] = sy;
	m.m[2][2] = sz;
	return (m);
}

// Function to create a rotation matrix around the X axis
t_matrix	create_rotation_x_matrix(double angle)
{
	double		c;
	double		s;
	t_matrix	m;

	c = cos(angle);
	s = sin(angle);
	m = create_identity_matrix();
	m.m[1][1] = c;
	m.m[1][2] = -s;
	m.m[2][1] = s;
	m.m[2][2] = c;
	return (m);
}

// Function to create a rotation matrix around the y axis
t_matrix	create_rotation_y_matrix(double angle)
{
	double		c;
	double		s;
	t_matrix	m;

	c = cos(angle);
	s = sin(angle);
	m = create_identity_matrix();
	m.m[0][0] = c;
	m.m[0][2] = s;
	m.m[2][0] = -s;
	m.m[2][2] = c;
	return (m);
}

// Function to create a rotation matrix around the z axis
t_matrix	create_rotation_z_matrix(double angle)
{
	double		c;
	double		s;
	t_matrix	m;

	c = cos(angle);
	s = sin(angle);
	m = create_identity_matrix();
	m.m[0][0] = c;
	m.m[0][1] = -s;
	m.m[1][0] = s;
	m.m[1][1] = c;
	return (m);
}

// Function to create a translation matrix
t_matrix	create_translation_matrix(double tx, double ty, double tz)
{
	t_matrix	m;

	m = create_identity_matrix();
	m.m[0][3] = tx;
	m.m[1][3] = ty;
	m.m[2][3] = tz;
	return (m);
}
