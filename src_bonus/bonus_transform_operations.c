/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_operations.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:47:42 by rhvidste          #+#    #+#             */
/*   Updated: 2025/02/11 15:44:20 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	orthographic_rotation(t_data *data)
{
	t_matrix	rot_x;
	t_matrix	rot_z;

	rot_x = create_rotation_x_matrix(deg_to_rad(45));
	rot_z = create_rotation_z_matrix(deg_to_rad(45));
	multiply_points(data, &rot_z);
	multiply_points(data, &rot_x);
}
