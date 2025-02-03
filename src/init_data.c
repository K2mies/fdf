/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:42:07 by rhvidste          #+#    #+#             */
/*   Updated: 2025/02/03 16:43:46 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
	// data->width = 0;
	// data->height = 0;
	// data->x_max = 0;
	// data->y_max = 0;
	// data->len = 0;
	// data->rows = 0;
	// data->cols = 0;
	// data->fd = 0;
	// data->line = 0;
	// data->points = NULL;
	// data->p2d = NULL;
	// data->img = NULL;
	// data->mlx = NULL;
	// data->o = NULL;
	return (data);
}

void	init_3d_points(t_data *data)
{
	int	i;

	i = -1;
	data->points = malloc(sizeof(t_vec4 *) * data->rows);
	if (!data->points)
		ft_printf("point failure\n");
	while (++i < data->rows)
	{
		//data->points[i] = malloc(sizeof(t_vec4) * data->cols);
		//uses calloc to initalize the points removing the need for memset.
		//remember to remove memset from files and header.
		data->points[i] = calloc(data->cols, sizeof(t_vec4));
		if (!data->points[i])
		{
			while (i--)
				free(data->points[i]);
			free(data->points);
			ft_printf("data points free'd");
			exit(1);
		}
	}
}

void	init_2d_points(t_data *data)
{
	int	i;

	i = -1;
	data->p2d = malloc(sizeof(t_vec2 *) * data->rows);
	if (!data->p2d)
		ft_printf("point failure\n");
	while (++i < data->rows)
	{
		//data->points[i] = malloc(sizeof(t_vec4) * data->cols);
		//uses calloc to initalize the points removing the need for memset.
		//remember to remove memset from files and header.
		data->p2d[i] = calloc(data->cols, sizeof(t_vec2));
		if (!data->p2d[i])
		{
			while (i--)
				free(data->p2d[i]);
			free(data->p2d);
			ft_printf("data points free'd");
			exit(1);
		}
	}
}
// Can remove this function as it is not relaly usefull anymore.
// or might still be usefull for implamenting colour 
//initalization at some point.
//might need to keep it in to initalize .w variable to 1.0 also.
void	memset_points(t_data *data)
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
			data->points[i][j].x = 0;
			data->points[i][j].y = 0;
			data->points[i][j].z = 0;
			data->points[i][j].w = 1;
			data->points[i][j].rgba = ft_atoi_base("0xFFFFFFFF", 16);
			j++;
		}
		i++;
	}
}

// Function to init orthographic data
void	init_ortho_data(t_data *data)
{
	data->o = malloc(sizeof(t_ortho_data));
	data->o->left = 00.0f;
	data->o->right = 00.0f;
	data->o->bottom = 00.0f;
	data->o->top = 00.0f;
	data->o->near = 00.0f;
	data->o->far = 00.0f;
}

// Function to init line data
void	init_line_data(t_data *data)
{
	data->ld = malloc(sizeof(t_line_data));
//	ft_memset(data->ld, 0, sizeof(t_line_data));
	data->ld->dx = 0;
	data->ld->sx = 0;
	data->ld->dy = 0;
	data->ld->sy = 0;
	data->ld->err = 0;
	data->ld->e2 = 0;
	data->ld->x0 = 0;
	data->ld->y0 = 0;
	data->ld->x1 = 0;
	data->ld->y1 = 0;
	data->ld->len = 0;
	data->ld->pix = 0;
	data->ld->color = WHITE;
}
