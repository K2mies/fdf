/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 11:30:00 by rhvidste          #+#    #+#             */
/*   Updated: 2025/01/27 10:30:32 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	reset_parse(char **argv, t_data *data, char **split, char **split2)
{
	split = NULL;
	split2 = NULL;
	data->fd = open(argv[1], O_RDONLY);
	data->line = get_next_line(data->fd);
	if (data->fd < 0 || !data->line)
		return (0);
	return (1);
}

int	parse_points(char **argv, t_data *data)
{	
	char	**split;
	char	**split2;

	split = NULL;
	split2 = NULL;
	data->fd = open(argv[1], O_RDONLY);
	data->line = get_next_line(data->fd);
	if (data->fd < 0 || !data->line)
		return (0);
	parse_xy_points(data);
	//parse_y_points(data, argv);
	parse_z_points(data, split, split2);
	reset_parse(argv, data, split, split2);
	//used to reset variables for each parse.
	parse_rgba_points(data, split, split2);
	//for parsing the rgba values use ft_atoi_base(char *str, int base)
	//in order to convert the number to an unsigned int.
	close(data->fd);
	return (1);
}

int	parse_xy_points(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < data->rows)
	{
		j = 0;
		while (j < data->cols)
		{
			data->points[i][j].y = (double)i;
			data->points[i][j].x = (double)j;
			j++;
		}
		i++;
	}
	return (1);
}

int	parse_z_points(t_data *data, char **split, char **split2)
{
	int		i;
	int		j;

	i = -1;
	j = -1;
	while (data->line && ++i < data->rows)
	{
		split = ft_split(data->line, ' ');
		j = -1;
		while (split[++j] && j < data->cols)
		{
			if (ft_strchr(split[j], ','))
			{
				split2 = ft_split(split[j], ',');
				data->points[i][j].z = (double)ft_atoi(split2[0]);
				free_arr(split2);
			}
			data->points[i][j].z = (double)ft_atoi(split[j]);
		}
		free(data->line);
		free_arr(split);
		data->line = get_next_line(data->fd);
	}
	return (1);
}

int	parse_rgba_points(t_data *data, char **split, char **split2)
{
	int		i;
	int		j;

	i = -1;
	j = -1;
	while (data->line && ++i < data->rows)
	{
		split = ft_split(data->line, ' ');
		j = -1;
		while (split[++j] && j < data->cols)
		{
			if (ft_strchr(split[j], ','))
			{
				split2 = ft_split(split[j], ',');
				data->points[i][j].rgba = ft_atoi_base(split2[1], 16);
				free_arr(split2);
			}
		}
		free(data->line);
		free_arr(split);
		data->line = get_next_line(data->fd);
	}
	return (1);
}
