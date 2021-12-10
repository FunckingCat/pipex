/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork_proc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unix <unix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 12:45:48 by unix              #+#    #+#             */
/*   Updated: 2021/12/10 13:23:50 by unix             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	fork_proc(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->cmds)
	{
		env->pids[i] = fork();
		if (env->pids[i] == -1)
			error("fork", "fork failed");
		else if (env->pids[i] == 0)
		{
			exec(&env->commands[i], env);
		}
		i++;
	}
}