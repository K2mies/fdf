/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:57:59 by rhvidste          #+#    #+#             */
/*   Updated: 2025/02/04 16:51:32 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Error function for mlx
void	ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

// Function to validate map
bool	validate_map(int argc, char **argv)
{
	char	*temp;

	temp = NULL;
	if (argc != 2)
	{
		ft_printf("invalid amount of arguments given\n");
		return (false);
	}
	if (ft_strnstr(argv[1], ".fdf", ft_strlen(argv[1])))
	{
		temp = ft_strnstr(argv[1], ".fdf", ft_strlen(argv[1]));
		if (temp[4] != '\0')
		{
			printf("is not a valid filetype\n");
			return (false);
		}
	}
	else
	{
		ft_printf("is not a valid .fdf filetype\n");
		return (false);
	}
	return (true);
}
