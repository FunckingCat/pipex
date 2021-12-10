/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open_in_out.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unix <unix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 20:22:10 by unix              #+#    #+#             */
/*   Updated: 2021/12/10 13:59:30 by unix             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check_file(char *file_path, int mode, int err)
{
	if (!access(file_path, 0))
	{
		if (access(file_path, mode))
			error(file_path, "Permission denied");
	}
	else
	{
		if (err)
			error(file_path, "No such file or directory");
	}
}

void	open_descriptors(int ac, char **av, int *arr)
{
	check_file(av[0], 4, 1);
	check_file(av[ac - 1], 2, 0);
	arr[0] = open(av[0], O_RDONLY);
	arr[1] = open(av[ac - 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
}
