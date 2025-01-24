/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 11:30:00 by rhvidste          #+#    #+#             */
/*   Updated: 2025/01/24 11:44:11 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	parse_points(char **argv, t_data *data)
{
	
	//parse_x_points(data, argv);
	//parse_y_points(data, argv);
	parse_z_points(data, argv);
	//parse_rgba_points(data, argv);
	//for parsing the rgba values use ft_atoi_base(char *str, int base)
	//in order to convert the number to an unsigned int.
}

int	parse_z_points(t_data *data, char **argv)
{
	int		i;
	int		j;
	int		fd;
	char	*line;
	char	**split;
	char	**split2;

	i = 0;
	j = 0;
	fd = open(argv[1], O_RDONLY);
	line = get_next_line(fd);
	if (fd < 0 || !line)
		return (0);
	while (line && i < data->rows)
	{
		split = ft_split(line, ' '); //split the line into columns
		j = 0;
		while(split[j] && j < data->cols) //itterate through the split
		{
			if (ft_strchr(split[j], ',')) //detect if there is a hex color value
			{
				split2 = ft_split(split[j], ','); //split again to seperate the color value
				data->points[i][j].z = (double)ft_atoi(split2[0]); //allocate as double
				data->points[i][j].rgba = ft_atoi_base(split2[1], 16); //allocating col data here but might be better to do it seperatly.
				free_arr(split2);
			}
			data->points[i][j].z = (double)ft_atoi(split[j]); //allocate as double.
			j++;
		}
		free(line);
		free_arr(split);
		line = get_next_line(fd);
		i++;
	}
	return (1);
}
