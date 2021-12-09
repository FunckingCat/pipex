/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_validate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unix <unix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 20:22:10 by unix              #+#    #+#             */
/*   Updated: 2021/12/09 15:44:25 by unix             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check_file(char *file_path, int mode, int err)
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
		if (err)
		{
			ft_putstr_fd(file_path, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			exit(EXIT_FAILURE);
		}
	}
}

// Значение	Проверяет
// 0	Существование файла
// 1	Исполняемость файла
// 2	Доступность для записи
// 3	Доступность для чтения
// 4	Доступность для чтения/записи

void	open_descriptors(int ac, char **av, int *arr)
{
	for (int i = 0; i < ac; i++)
		printf("%s\n", av[i]);
	check_file(av[0], 4, 1);
	check_file(av[ac - 1], 2, 0);
	arr[0] = open(av[0], O_RDONLY);
	arr[1] = open(av[ac - 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
}