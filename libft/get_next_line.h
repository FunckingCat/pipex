/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unix <unix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 17:37:18 by unix              #+#    #+#             */
/*   Updated: 2021/12/10 15:45:33 by unix             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# define BUFFER_SIZE 42

char	*get_next_line(int fd);

char	*ft_strchr(const char *s, int c);
size_t	ft_strl(const char *s);
void	*ft_memmove(void *dest, const void *src, size_t n);
char	*ft_strjo(char const *s1, char const *s2);

#endif
