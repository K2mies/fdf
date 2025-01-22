/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 10:29:55 by rhvidste          #+#    #+#             */
/*   Updated: 2025/01/22 18:06:01 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../lib/libft/libft.h"
# include "../lib/MLX42/include/MLX42/MLX42.h"
# include <math.h>
# include <fcntl.h>

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
		t_dp4	**points;
}		t_data;

//read map functions
int	print_map(char **argv); //prints the map to the terminal
int	get_row_count(char **argv, t_data *data); //gets the count of rows in the map.
int	get_col_count(char **argv, t_data *data); //gets the count of collumns in the map.
int	get_map_len(char **argv, t_data *data); //gets the len of the whole map
int	word_count(const char *str); //word counter

#endif
