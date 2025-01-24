/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:28:30 by rhvidste          #+#    #+#             */
/*   Updated: 2025/01/23 17:47:20 by rhvidste         ###   ########.fr       */
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

int		get_map_len(char **argv, t_data *data)
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
	return(rc);
}

int	get_col_count(char **argv, t_data *data)
{
	int		cc;
	int		fd;
	char	*line;
	char	**split;

	fd = open(argv[1], O_RDONLY);
	line = get_next_line(fd);
	if (fd < 0 || !line)
		return (0);
	cc = 0;
	split = ft_split(line, ' ');
	while (split[cc])
		cc++;
	//it needs to run through every line here even if it doesnt use them
	// in order to free memory correctly. ------------------------------
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
	//-------------------------------------------------------------------
	free(line);
	free(split);
	close(fd);
	data->cols = cc;
	return (cc);
}

int	print_map(char **argv)
{	
	int		fd;
	char	*line;

	fd = open(argv[1], O_RDONLY);
	line = get_next_line(fd);
	if (fd < 0 || !line)
		return (0);
	while (line)
	{
		ft_printf("%s\n", line);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return (1);
}

// Remember to remove this function from the submition branch as it uses printf
// Which is an ilegal function for our submitions.
// Also remember to remove #include <stdio.h> from your header file. 
int	print_arr(t_data *data, char flag)
{
	int	i;
	int	j;

	i = 0;
	j = 0;

	while (i < data->rows)
	{
		j = 0;
		while(j < data->cols)
		{
			if (flag == 'x')
				printf("%.1f ", data->points[i][j].x);
			if (flag == 'y')
				printf("%.1f ", data->points[i][j].y);
			if (flag == 'z')
				printf("%.1f ", data->points[i][j].z);
			if (flag == 'c')
				printf("%x ", data->points[i][j].rgba);
				//printf("%.1u ", data->points[i][j].rgba);
			j++;
		}
		printf("\n");
		i++;
	}
	return (1);
}
