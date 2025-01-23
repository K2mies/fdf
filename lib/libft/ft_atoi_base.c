/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 16:18:44 by rhvidste          #+#    #+#             */
/*   Updated: 2025/01/23 17:10:33 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isvalid(char ch, int base)
{
	char	*lcbase;
	char	*ucbase;
	int		i;

	lcbase = "0123456789abcdef";
	ucbase = "0123456789ABCDEF";
	i = 0;
	while (i < base)
	{
		if (ch == lcbase[i] || ch == ucbase[i])
			return (1);
		i++;
	}
	return (0);
}

unsigned int	ft_parse(int i, char *str, int base)
{
	unsigned int	res;
	int				c;

	while (str[i] && ft_isvalid(str[i], base))
	{
		if (str[i] >= '0' && str[i] <= '9')
			c = str[i] - '0';
		if (str[i] >= 'a' && str[i] <= 'f')
			c = str[i] - 'a' + 10;
		if (str[i] >= 'A' && str[i] <= 'F')
			c = str[i] - 'A' + 10;
		i++;
		res = res * base + c;
	}
	return (res);
}

unsigned int	ft_atoi_base(char *str, int base)
{
	int				sign;
	unsigned int	res;
	int				i;

	sign = 1;
	res = 0;
	i = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
	{
		sign *= -1;
		i++;
	}
	if (str[i] == '+')
		i++;
	res = ft_parse(i, str, base);
	return (res * sign);
}
