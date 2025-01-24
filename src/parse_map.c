/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 11:30:00 by rhvidste          #+#    #+#             */
/*   Updated: 2025/01/24 14:54:49 by rhvidste         ###   ########.fr       */
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
	//parse_x_points(data, argv);
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

int	parse_z_points(t_data *data, char **split, char **split2)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	/*int		fd;
	char	*line;
	char	**split;
	char	**split2;

	i = 0;
	j = 0;
	fd = open(argv[1], O_RDONLY);
	if (fd < 0 || !line)
		return (0);
	*/
	//line = get_next_line(fd);
	while (data->line && i < data->rows)
	{
		split = ft_split(data->line, ' ');
		//split the line into columns
		j = 0;
		while (split[j] && j < data->cols)
		//itterate through the split
		{
			if (ft_strchr(split[j], ','))
			//detect if there is a hex color value
			{
				split2 = ft_split(split[j], ',');
				//split again to seperate the color value
				data->points[i][j].z = (double)ft_atoi(split2[0]);
				//allocate as double
				//data->points[i][j].rgba = ft_atoi_base(split2[1], 16); 
				//allocating col data here but might be better to do it seperatly.
				free_arr(split2);
			}
			data->points[i][j].z = (double)ft_atoi(split[j]);
			//allocate as double.
			j++;
		}
		free(data->line);
		free_arr(split);
		data->line = get_next_line(data->fd);
		i++;
	}
	return (1);
}

int	parse_rgba_points(t_data *data, char **split, char **split2)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (data->line && i < data->rows)
	{
		split = ft_split(data->line, ' ');
		j =0;
		while (split[j] && j < data->cols)
		{
			if (ft_strchr(split[j], ','))
			{
				split2 = ft_split(split[j], ',');
				data->points[i][j].rgba = ft_atoi_base(split2[1], 16);
				free_arr(split2);
			}
			j++;
		}
		free(data->line);
		free_arr(split);
		data->line = get_next_line(data->fd);
		i++;
	}
	return (1);
}
