/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 10:47:40 by rhvidste          #+#    #+#             */
/*   Updated: 2025/01/23 17:37:30 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fdf.h"

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
				data->points[i][j].rgba = ft_atoi_base(split2[1], 16);
				free(split2);
			}
			data->points[i][j].z = (double)ft_atoi(split[j]); //allocate as double.
			j++;
		}
		free(line);
		free(split);
		line = get_next_line(fd);
		i++;
	}
	return (1);
}

void	parse_points(char **argv, t_data *data)
{
	//parse_x_points(data, argv);
	//parse_y_points(data, argv);
	parse_z_points(data, argv);
	//parse_rgba_points(data, argv);
	//for parsing the rgba values use ft_atoi_base(char *str, int base)
	//in order to convert the number to an unsigned int.
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		return (0);

	t_data *data;
	data = init_data();
	get_map_len(argv, data);
	get_row_count(argv, data);
	get_col_count(argv, data);
	init_points(data);
	//ft_printf("len = %d\nrows = %d\ncolumns = %d\n", data->len, data->rows, data->cols);
	//print_map(argv);
	//memset_points(data); // you do not need memset anymore as calloc initalizes the points.
	parse_points(argv, data);
	print_arr(data, 'x');
	printf("\n");
	print_arr(data, 'z');
	printf("\n");
	print_arr(data, 'c');

	free_arr(data);
	free(data);
}

