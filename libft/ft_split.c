/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyamcha <tyamcha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 14:34:30 by tyamcha           #+#    #+#             */
/*   Updated: 2021/10/14 16:43:23 by tyamcha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
