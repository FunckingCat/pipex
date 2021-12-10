/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unix <unix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 10:47:22 by tyamcha           #+#    #+#             */
/*   Updated: 2021/12/10 13:39:16 by unix             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_command	*who_returned(t_env *env, pid_t pid)
{
	int	i;
	
	i = 0;
	while (i < env->cmds)
	{
		if(env->pids[i] == pid)
			return (&env->commands[i]);
		i++;
	}
	return (NULL);
}

void	wait_children(t_env *env)
{
	int	i;
	int	ret;
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

// void	print_env(t_env *env)
// {
// 	printf("----------ENV-------------\n");
// 	printf("Commands %d\n", env->cmds);
// 	for (int i = 0; i < env->cmds; i++)
// 	{
// 		printf("%s\n", env->commands[i].arg);
// 		printf("%d %d\n", env->commands[i].in, env->commands[i].out);
// 	}
// 	printf("--------------------------\n");
// }

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;

	if (argc < 4)
		error("too few args", "usage ./pipex ./in \"cmd1\" \"cmd2\" ./out");

	env = make_env(argc, argv, envp);
	fork_proc(env);
	wait_children(env);
	printf("Parent\n");
	return (0);
}
