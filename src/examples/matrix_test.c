/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rvidste@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 18:42:08 by rhvidste          #+#    #+#             */
/*   Updated: 2025/01/25 23:20:30 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//Define a 4x4 matrix structure.
typedef struct s_matrix
{
	double	m[4][4];
}	t_matrix;

//Define a 3d vector structure
typedef struct s_vec4
{
	double	x;
	double	y;
	double	z;
	double	w;
}	t_vec4;

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
	//double	w;
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
	return (res);
}

// Function to create a translation matrix
t_matrix	create_translation_matrix(double tx, double ty, double tz)
{
	t_matrix m;
	m = create_identity_matrix();
	m.m[0][3] = tx;
	m.m[1][3] = ty;
	m.m[2][3] = tz;
	return (m);
}

// Function to create a scaling matrix
t_matrix	create_scaling_matrix(double sx, double sy, double sz)
{
	t_matrix	m = create_identity_matrix();
	m.m[0][0] = sx;
	m.m[1][1] = sy;
	m.m[2][2] = sz;
	return (m);
}

// Function to create a rotation matrix around the X axis
t_matrix	create_rotation_x_matrix(double angle)
{
	double	c;
	double	s;

	c = cos(angle);
	s = sin(angle);
	t_matrix	m;
       	m = create_identity_matrix();
	m.m[1][1] = c;
	m.m[1][2] = -s;
	m.m[2][1] = s;
	m.m[2][2] = c;
	return(m);
}

// Function to create a rotation matrix around the y axis
t_matrix	create_rotation_y_matrix(double angle)
{
	double	c;
	double	s;

	c = cos(angle);
	s = sin(angle);
	t_matrix	m;
	m = create_identity_matrix();
	m.m[0][0] = c;
	m.m[0][2] = s;
	m.m[2][0] = -s;
	m.m[2][2] = c;
	return (m);
}

t_matrix	create_rotation_z_matrix(double angle)
{
	double	c;
	double	s;

	c = cos(angle);
	s = sin(angle);
	t_matrix	m;
	m = create_identity_matrix();
	m.m[0][0] = c;
	m.m[0][1] = -s;
	m.m[1][0] = s;
	m.m[1][1] = c;
	return (m);
}

// Function to normalize a homogeneous coordinate vector

t_vec4	normalize_homogeneous_vector(t_vec4 v)
{
	if (v.w != 0 && v.w != 1)
	{
		v.x /= v.w;
		v.y /= v.w;
		v.z /= v.w;
		v.w = 1;
	}
	return (v);
}

int	main(int argc, char **argv)
{
	(void)argc;
	double	x;
	double	y;
	double	z;
	double	w;

	x = atof(argv[1]);
	y = atof(argv[2]);
	z = atof(argv[3]);
	w = atof(argv[4]);

	t_vec4	v = {x, y, z, w}; // Homogenoeous coordinate(x, y, z, w)
	
	//t_matrix	translation;
	t_matrix	rot_x;
	//translation = create_translation_matrix(2, 3, 4);
	rot_x = create_rotation_x_matrix(15);
	
	t_vec4		res;

	//res = matrix_multiply_vector(translation, v);
	res = matrix_multiply_vector(rot_x, v);
	res = normalize_homogeneous_vector(res);

	printf("Original vector: (%.1f, %.1f, %.1f, %.1f)\n", v.x, v.y, v.z, v.w);
	printf("Translated vector(%.1f, %.1f, %.1f, %.1f)\n", res.x, res.y, res.z, res.w);
	return (0);
}

/*void	tranlate(t_dp4 *point, double offset)
{
	x_trans.elem = (double * [])
	{
		(double[]){1, 0, 0, offset},
		(double[]){0, 1, 0, offset},
		(double[]){0, 0, 1 ,offset}
		(double[]){0, 0, 0 ,1}
	};
}*/
