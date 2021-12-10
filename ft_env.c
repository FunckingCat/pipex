/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unix <unix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 11:09:45 by unix              #+#    #+#             */
/*   Updated: 2021/12/10 14:03:19 by unix             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	set_in_out(t_env *env, char **argv)
{
	int		i;
	int		pip[2];

	i = 1;
	while (i < env->cmds)
	{
		if (pipe(pip) == -1)
			error("pipe", "failed create a pipe");
		env->commands[i - 1].out = pip[1];
		env->commands[i].in = pip[0];
		env->commands[i].arg = argv[i + 2];
		i++;
	}
}

t_env	*make_env(int argc, char **argv, char **envp)
{
	int		inout[2];
	t_env	*env;

	open_descriptors(argc - 1, argv + 1, inout);
	env = malloc(sizeof(t_env));
	if (!env)
		error("malloc", "cant alloc mem");
	env->cmds = argc - 3;
	env->ep = envp;
	env->pids = malloc(sizeof(pid_t) * env->cmds);
	env->commands = malloc(sizeof(t_command) * env->cmds);
	env->commands[0].in = inout[0];
	env->commands[0].arg = argv[2];
	env->commands[env->cmds - 1].out = inout[1];
	set_in_out(env, argv);
	return (env);
}
