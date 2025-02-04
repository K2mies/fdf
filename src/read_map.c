/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:28:30 by rhvidste          #+#    #+#             */
/*   Updated: 2025/02/04 15:09:58 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fdf.h"

int	word_count(const char *str)
{
	int		wc;
	int		i;

	i = 0;
	wc = 0;
	while (str[i])
	{
		while (str[i] && (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
			i++;
		if (str[i])
			wc++;
		while (str[i] && (str[i] != ' ' && !(str[i] >= 9 && str[i] <= 13)))
			i++;
	}
	return (wc);
}

// Function to get the total len of the map grid.
int	get_map_len(char **argv, t_data *data)
{
	int		wc;
	int		fd;
	char	*line;

	fd = open(argv[1], O_RDONLY);
	line = get_next_line(fd);
	if (fd < 0 || !line)
		return (0);
	wc = 0;
	while (line)
	{
		wc += word_count(line);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	data->len = wc;
	return (wc);
}

// Function to get the len of rows.
int	get_row_count(char **argv, t_data *data)
{
	int		rc;
	int		fd;
	char	*line;

	fd = open(argv[1], O_RDONLY);
	line = get_next_line(fd);
	if (fd < 0 || !line)
		return (0);
	rc = 0;
	while (line)
	{
		rc++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	data->rows = rc;
	return (rc);
}

// Function to get collum len.
int	get_col_count(char **argv, t_data *data)
{
	int		cc;

	data->fd = open(argv[1], O_RDONLY);
	data->line = get_next_line(data->fd);
	if (data->fd < 0 || !data->line)
		return (0);
	cc = 0;
	data->split = ft_split(data->line, ' ');
	cc = arr_len(data->split);
	//it needs to run through every line here even if it doesnt use them
	// in order to free memory correctly. ------------------------------
	while (data->line)
	{
		free(data->line);
		data->line = get_next_line(data->fd);
	}
	//-------------------------------------------------------------------
	free(data->line);
	free_arr(data->split);
	close(data->fd);
	data->cols = cc;
	return (cc);
}

//// Function that gets col count and also checks if row lens are
//// unequal.
//int get_col_count(char **argv, t_data *data)
//{
//    int		cc;
//
//    data->fd = open(argv[1], O_RDONLY);
//    if (data->fd < 0 || !(data->line = get_next_line(data->fd)))
//        return (0);
//    data->split = ft_split(data->line, ' ');
//    cc = arr_len(data->split);
//    free_arr(data->split);
//    while (data->line)
//    {
//        free(data->line);
//        if ((data->line = get_next_line(data->fd)))
//        {
//            data->split = ft_split(data->line, ' ');
//            if (cc != arr_len(data->split))
//			{
//                ft_printf("invalid map, columns not equal\n");
//				free(data);
//				exit(EXIT_FAILURE);
//			}
//            free_arr(data->split);
//        }
//    }
//    close(data->fd);
//    data->cols = cc;
//    return (cc);
//}

//// Function to print the map
//int	print_map(char **argv)
//{	
//	int		fd;
//	char	*line;
//
//	fd = open(argv[1], O_RDONLY);
//	line = get_next_line(fd);
//	if (fd < 0 || !line)
//		return (0);
//	while (line)
//	{
//		ft_printf("%s\n", line);
//		free(line);
//		line = get_next_line(fd);
//	}
//	free(line);
//	close(fd);
//	return (1);
//}

// Remember to remove this function from the submition branch as it uses printf
// Which is an ilegal function for our submitions.
// Also remember to remove #include <stdio.h> from your header file. 
int	print_arr(t_data *data, char flag)
{
	int	i;
	int	j;

	i = -1;
	while (++i < data->rows)
	{
		j = -1;
		while (++j < data->cols)
		{
			if (flag == 'x')
				ft_printf("%.1f ", data->points[i][j].x);
			if (flag == 'y')
				ft_printf("%.1f ", data->points[i][j].y);
			if (flag == 'z')
				ft_printf("%.1f ", data->points[i][j].z);
			if (flag == 'w')
				ft_printf("%.1f ", data->points[i][j].w);
			if (flag == 'c')
				ft_printf("%X ", data->points[i][j].rgba);
		}
		printf("\n");
	}
	return (1);
}
