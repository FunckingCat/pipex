/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unix <unix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 14:34:30 by tyamcha           #+#    #+#             */
/*   Updated: 2021/12/09 16:34:28 by unix             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

size_t	ft_strlen(const char *s)
{
	int	res;

	res = 0;
	while (*s++)
		res++;
	return (res);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	int	n;

	n = 0;
	if (src == NULL)
	{
		*dst = '\0';
		return (0);
	}
	if (size == 0)
	{
		return (ft_strlen(src));
	}
	while (*src && --size > 0 && n++ > -1)
		*dst++ = *src++;
	*dst = '\0';
	return (ft_strlen(src - n));
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == c % 256)
			return ((char *)s);
		s++;
	}
	if (*s == c % 256)
		return ((char *)s);
	return (NULL);
}

static	size_t	ft_count_words(char const *s, char c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			count++;
			while (*s && *s != c)
				s++;
		}
	}
	return (count);
}

static void	ft_free_res(char **res)
{
	size_t	i;

	i = 0;
	while (res[i])
		free(res[i++]);
	free(res);
}

static	char	**ft_body(char **res, size_t count, char const *s, int c)
{
	char	*end;
	size_t	i;

	i = 0;
	while (i < count)
	{
		while (*s == c)
			s++;
		end = ft_strchr(s, c);
		if (!end)
			end = ft_strchr(s, '\0');
		res[i] = malloc(end - s + 1);
		if (!res[i])
		{
			ft_free_res(res);
			return (NULL);
		}
		ft_strlcpy(res[i++], s, end - s + 1);
		while (*s && *s != c)
			s++;
	}
	res[i] = NULL;
	return (res);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	size_t	count;

	if (!s)
		return (NULL);
	count = ft_count_words(s, c);
	res = malloc((count + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	res = ft_body(res, count, s, c);
	if (!res)
		return (NULL);
	return (res);
}

char	*ft_strdup(const char *s1)
{
	char	*res;

	res = malloc((ft_strlen(s1) + 1) * sizeof(char));
	if (res == NULL)
		return (NULL);
	ft_strlcpy(res, s1, ft_strlen(s1) + 1);
	return (res);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	size_t	res_len;

	if (!s1 || !s2)
		return (NULL);
	res_len = ft_strlen(s1) + ft_strlen(s2);
	res = (char *)malloc(sizeof(char) * (res_len + 1));
	if (!res)
		return (NULL);
	while (*s1)
		*res++ = *s1++;
	while (*s2)
		*res++ = *s2++;
	*res = '\0';
	return (res - res_len);
}
