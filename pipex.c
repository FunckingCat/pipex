/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unix <unix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 10:47:22 by tyamcha           #+#    #+#             */
/*   Updated: 2021/12/10 15:36:20 by unix             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error(char *name, char *desc)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(name, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(desc, 2);
	ft_putstr_fd("\n", 2);
	exit(EXIT_FAILURE);
}

t_command	*who_returned(t_env *env, pid_t pid)
{
	int	i;

	i = 0;
	while (i < env->cmds)
	{
		if (env->pids[i] == pid)
			return (&env->commands[i]);
		i++;
	}
	return (NULL);
}

void	wait_children(t_env *env)
{
	int			i;
	int			ret;
	t_command	*child;

	i = 0;
	while (i < env->cmds)
	{
		ret = wait(NULL);
		child = who_returned(env, ret);
		if (child)
		{
			if (child->out != 1)
				close(child->out);
			if (child->in != 0)
				close(child->in);
		}
		i++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;

	if (argc < 4)
		error("too few args", "usage ./pipex ./in \"cmd1\" \"cmd2\" ./out");
	env = make_env(argc - 1, argv + 1, envp);
	fork_proc(env);
	wait_children(env);
	free(env->pids);
	free(env->commands);
	free(env);
	return (0);
}
