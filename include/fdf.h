/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 10:29:55 by rhvidste          #+#    #+#             */
/*   Updated: 2025/01/24 14:41:30 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../lib/libft/libft.h"
# include "../lib/MLX42/include/MLX42/MLX42.h"
# include <math.h>
# include <fcntl.h>
# include <stdint.h>
# include <stdio.h>

# define WIDTH 2048
# define HEIGHT 2048

# define RED	0xFF0000FF
# define GREEN	0x00FF00FF
# define BLUE	0x0000FFFF
# define WHITE	0x000000FF
# define BLACK	0x000000FF

typedef struct	s_dp4
{
		double			x;
		double			y;
		double			z;
		unsigned int	rgba;
}		t_dp4;

typedef struct s_data
{
		int		len;
		int		rows;
		int		cols;
		int		fd;
		char	*line;
		t_dp4	**points;
}		t_data;

//read map functions------------------------------------------------------------------
int		print_map(char **argv); //prints the map to the terminal
int		get_row_count(char **argv, t_data *data); //gets the count of rows in the map.
int		get_col_count(char **argv, t_data *data); //gets the count of collumns in the map.
int		get_map_len(char **argv, t_data *data); //gets the len of the whole map
int		word_count(const char *str); //word counter
int		print_arr(t_data *data, char flag); //function to print the points array.

//parse map--------------------------------------------------------------------------
int		parse_points(char **argv, t_data *data);
int		reset_parse(char **argv, t_data *data, char **split, char **split2);
int		parse_z_points(t_data *data, char **split, char **split2);
int		parse_rgba_points(t_data *data, char **split, char **split2);
//init_data---------------------------------------------------------------------------
t_data	*init_data();
void	init_points(t_data *data);
void	memset_points(t_data *data);

//utils-------------------------------------------------------------------------------
void	free_point_arr(t_data *data);
void	free_arr(char **arr);

#endif
