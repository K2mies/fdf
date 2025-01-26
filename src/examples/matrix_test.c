/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rvidste@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 18:42:08 by rhvidste          #+#    #+#             */
/*   Updated: 2025/01/26 22:13:31 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//Homogeneous Coordinates system.

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

//Define a 2d vector structure
typedef struct s_vec2
{
	double	x;
	double	y;
}	t_vec2;

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

// Function to projcet 3d to 2d space
void project_3d_to_2d(double x, double y, double z, t_matrix proj_matrix, t_vec2 *res) 
{
    double w;
    	 w =  	    proj_matrix.m[3][0] * x + proj_matrix.m[3][1] * y + proj_matrix.m[3][2] * z + proj_matrix.m[3][3];
    res->x = 100 * (proj_matrix.m[0][0] * x + proj_matrix.m[0][1] * y + proj_matrix.m[0][2] * z + proj_matrix.m[0][3]) / w;
    res->y = 100 * (proj_matrix.m[1][0] * x + proj_matrix.m[1][1] * y + proj_matrix.m[1][2] * z + proj_matrix.m[1][3]) / w;
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

// Function to create a rotation matrix around the z axis
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

// Function to create a orthographic perspective matrix
t_matrix	create_orthographic_matrix(double left, double right, double bottom, double top, double near, double far)
{
	t_matrix	m = {{{0}}};
        //m = create_identity_matrix();

	m.m[0][0] =  2.0f / (right - left);
	m.m[1][1] =  2.0f / (top - bottom);
	m.m[2][2] = -2.0f / (far - near);
	m.m[3][0] = -(right + left) / (right - left);
	m.m[3][1] = -(top + bottom) / (top - bottom);
	m.m[3][2] = -(far + near) / (far - near);
	m.m[3][3] =  1.0f;

	return(m);
}

// Function to create a perspective matrix for projection.
t_matrix	create_perspective_matrix(double fov, double aspect_ratio, double near, double far)
{
	t_matrix	m = {{{0}}}; // Initialize all ememnts to 0
	double tan_half_fov;
	tan_half_fov = tan(fov * 0.5 * M_PI / 180.0);

	m.m[0][0] =  1.0f / (aspect_ratio * tan_half_fov);
	m.m[1][1] =  1.0f / tan_half_fov;
	m.m[2][2] =  (far + near) / (far - near);
	m.m[2][3] = -2.0f * far * near / (far - near);
	m.m[3][2] = -1.0f;

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

	// Here we create the matricies	
	t_matrix	scale;
	t_matrix	rot_x;
	t_matrix	rot_y;
	t_matrix	rot_z;
	t_matrix	translation;
	t_matrix	orthographic;
	//t_matrix	perspective;
	
	// Here we set the matricies
	scale = create_scaling_matrix(3, 3, 3);
	rot_x = create_rotation_x_matrix(15);
	rot_y = create_rotation_y_matrix(15);
	rot_z = create_rotation_z_matrix(15);	
	translation = create_translation_matrix(10, 10, 10);
	orthographic = create_orthographic_matrix(-10.0f, 10.0f, -7.5f, 7.5f, 0.1f, 100.0f);
	//perspective = create_perspective_matrix(60.0, (16.0 / 9.0), 0.1, 100.0);
	//				       |fov  |aspect ratio| near |far

	// Here we apply the matricies (in correct order) using matrix multiplication
	t_vec4		res;// Vector pre projection.----------------------------------------
	res = matrix_multiply_vector(scale, v);
	res = matrix_multiply_vector(rot_x, res);
	res = matrix_multiply_vector(rot_y, res);
	res = matrix_multiply_vector(rot_z, res);
	res = matrix_multiply_vector(translation, res);
	t_vec4		res2; // Vector post projection.-------------------------------------
	res2 = matrix_multiply_vector(orthographic, res);
	t_vec2		res3; // 2D projection of Vector-------------------------------------
	project_3d_to_2d(res2.x, res2.y, res2.z, orthographic, &res3);
	//res = matrix_multiply_vector(perspective, v);

	//res = normalize_homogeneous_vector(res);
	

	printf("Original vector: (%.1f, %.1f, %.1f, %.1f)\n", v.x, v.y, v.z, v.w);
	printf("Translated vector(pre-projection)(%.1f, %.1f, %.1f, %.1f)\n", res.x, res.y, res.z, res.w);
	printf("Translated Vector(post-projection)(%.1f, %.1f, %.1f, %.1f)\n", res2.x, res2.y, res2.z, res2.w);
	printf("2d vector result(%2.f, %2.f)", res3.x, res3.y);
	return (0);       
}
