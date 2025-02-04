/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:42:07 by rhvidste          #+#    #+#             */
/*   Updated: 2025/02/04 11:24:34 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Function to initialize global data
t_data	*init_data(void)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
	{
		perror("Failed to allocate memory for data");
		exit(EXIT_FAILURE);
	}
	ft_memset(data, 0, sizeof(t_data));
	return (data);
}

// Function to init orthographic data
void	init_ortho_data(t_data *data)
{
	data->o = malloc(sizeof(t_ortho_data));
	ft_memset(data->o, 0, sizeof(t_ortho_data));
}

// Function to init line data
void	init_line_data(t_data *data)
{
	data->ld = malloc(sizeof(t_line_data));
	ft_memset(data->ld, 0, sizeof(t_line_data));
	data->ld->color = WHITE;
}

// Function to init gradient data
void	init_gradient_data(t_data *data)
{
	data->gd = malloc(sizeof(t_gradient_data));
	ft_memset(data->gd, 0, sizeof(t_gradient_data));
	data->gd->alpha = 255;
}
