/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unix <unix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 11:09:45 by unix              #+#    #+#             */
/*   Updated: 2021/12/10 15:39:33 by unix             ###   ########.fr       */
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

void	open_descriptors(int ac, char **av, t_env *env)
{
	check_file(av[0], 4, 1);
	check_file(av[ac - 1], 2, 0);
	env->commands[0].in = open(av[0], O_RDONLY);
	env->commands[env->cmds - 1].out = open(av[ac - 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
}

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
		env->commands[i].arg = argv[i + 1];
		i++;
	}
}

t_env	*make_env(int argc, char **argv, char **envp)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (!env)
		error("malloc", "cant alloc mem");
	env->cmds = argc - 2;
	env->ep = envp;
	env->pids = malloc(sizeof(pid_t) * env->cmds);
	env->commands = malloc(sizeof(t_command) * env->cmds);
	env->commands[0].arg = argv[1];
	open_descriptors(argc, argv, env);
	set_in_out(env, argv);
	return (env);
}
