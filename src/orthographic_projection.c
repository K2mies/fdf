/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   orthographic_projection.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:30:40 by rhvidste          #+#    #+#             */
/*   Updated: 2025/02/04 16:11:52 by rhvidste         ###   ########.fr       */
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
	ortho_project(data, orthographic);
}
