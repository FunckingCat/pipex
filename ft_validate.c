/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_validate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unix <unix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 20:22:10 by unix              #+#    #+#             */
/*   Updated: 2021/12/07 21:09:16 by unix             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check_file(char *file_path, int mode)
{
	if (!access(file_path, 0))
	{
		if (access(file_path, mode))
		{
			ft_putstr_fd(file_path, 2);
			ft_putstr_fd(": Permission denied\n", 2);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		ft_putstr_fd(file_path, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		exit(EXIT_FAILURE);
	}
}

// Значение	Проверяет
// 0	Существование файла
// 1	Исполняемость файла
// 2	Доступность для записи
// 3	Доступность для чтения
// 4	Доступность для чтения/записи

void	validate(int ac, char **av)
{
	for (int i = 0; i < ac; i++)
		printf("%s\n", av[i]);
	check_file(av[0], 0);
	check_file(av[ac - 1], 0);
}