/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 15:44:33 by rhvidste          #+#    #+#             */
/*   Updated: 2025/01/20 11:05:31 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

//char	*ft_strchr(const char *s, int c);
//char	*ft_strdup(const char *s);
//char	*ft_substr(const char *s, unsigned int start, size_t len);
//char	*ft_strjoin(const char *s1, const char *s2);
//size_t	ft_strlen(const char *str);

char	*get_next_line(int fd);

#endif
