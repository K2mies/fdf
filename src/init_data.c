/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 10:11:41 by rhvidste          #+#    #+#             */
/*   Updated: 2025/01/28 10:51:27 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_data	*init_data(void)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->width = 0;
	data->height = 0;
	data->len = 0;
	data->rows = 0;
	data->cols = 0;
	data->fd = 0;
	data->line = 0;
	data->points = NULL;
	data->img = NULL;
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
//might need to keep it in to initalize .w variable to 1.0.
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
			data->points[i][j].rgba = 0;
			ft_printf("%d\n", data->points[i][j].z);
			j++;
		}
		i++;
	}
}
