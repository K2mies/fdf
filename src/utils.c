/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 10:18:08 by rhvidste          #+#    #+#             */
/*   Updated: 2025/01/27 10:30:38 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_arr(char **arr)
{
	int	i;
	i = 0;
	while (arr[i])
	{
		free(arr[i++]);
	}
	free(arr);
}

void	free_point_arr(t_data *data)
{
	int		i;
	i = -1;
	while(++i < data->rows)
		free(data->points[i]);
	free(data->points);
}
