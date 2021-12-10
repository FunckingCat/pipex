/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unix <unix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 10:47:22 by tyamcha           #+#    #+#             */
/*   Updated: 2021/12/10 13:11:10 by unix             ###   ########.fr       */
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

void	print_env(t_env *env)
{
	printf("----------ENV-------------\n");
	printf("Commands %d\n", env->cmds);
	for (int i = 0; i < env->cmds; i++)
	{
		printf("%s\n", env->commands[i].arg);
		printf("---> in %d; out %d\n", env->commands[i].in, env->commands[i].out);
	}
	printf("--------------------------\n");
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;

	env = make_env(argc, argv, envp);
	print_env(env);
	fork_proc(env);
	wait_children(env);
	printf("Parent\n");
	for (int i = 0; i < env->cmds; i++)
		printf("%d pid %d\n", i, env->pids[i]);
	return (0);
}

// int	main(int argc, char **argv, char **envp)
// {
// 	int		pip[2];
// 	int		inout[2];
// 	int		status1;
// 	int		status2;
// 	pid_t	fork_cmd1;
// 	pid_t	fork_cmd2;
// 	t_env	*env;

// 	if (argc < 5)
// 		error("usage", "file1 cmd1 cmd2 file2");
		
// 	open_descriptors(argc - 1, argv + 1, inout);

// 	env = malloc(sizeof(t_env));
// 	if (!env)
// 		error("malloc", "cant alloc mem");
// 	env->ac = argc - 3;
// 	env->av = argv + 2;
// 	env->ep = envp;
// 	env->inout = inout;

// 	proc(env);
// 	if (pipe(pip) == -1)
// 		error("pipe", "failed create a pipe");

// 	fork_cmd1 = fork();
// 	if (fork_cmd1 == -1)
// 		error("fork", "fork failed");
// 	else if (fork_cmd1 == 0)
// 	{
// 		close(pip[0]);
// 		dup2(inout[0], STDIN_FILENO);
// 		dup2(pip[1], STDOUT_FILENO);
// 		run(argv[2], envp);
// 	}

// 	fork_cmd2 = fork();
// 	if (fork_cmd2 == -1)
// 		error("fork", "fork failed");
// 	else if (fork_cmd2 == 0)
// 	{
// 		close(pip[1]);
// 		dup2(pip[0], STDIN_FILENO);
// 		dup2(inout[1], STDOUT_FILENO);
// 		wait(&fork_cmd1);
// 		run(argv[3], envp);
// 	}
	
// 	close(pip[1]);
// 	close(inout[0]);
// 	close(inout[1]);
// 	waitpid(fork_cmd1, &status1, 0);
// 	waitpid(fork_cmd2, &status2, 0);
// 	if (status1 || status2)
// 		printf("Error\n");
// 	else
// 		printf("Exited Normally\n");
// 	printf("Parent\n");
// 	return (0);
// }

// void	proc2(t_env *env, int n, int *prevpip, pid_t bro)
// {
// 	int		pip[2];
// 	pid_t	fork_cmd;
	
// 	if (pipe(pip) == -1)
// 		error("pipe", "failed create a pipe");
	
// 	fork_cmd = fork();
// 	if (fork_cmd == -1)
// 		error("fork", "fork failed");
// 	else if (fork_cmd == 0)
// 	{
// 		close(pip[0]);
// 		if (prevpip)
// 			close(prevpip[1]);
// 		if (n == 0)
// 			dup2(env->inout[0], STDIN_FILENO);
// 		else
// 			dup2(prevpip[0], STDIN_FILENO);
// 		if (n == env->ac - 1)
// 			dup2(env->inout[1], STDOUT_FILENO);
// 		else
// 			dup2(pip[1], STDOUT_FILENO);
// 		if (bro)
// 			wait(&bro);
// 		run(env->av[n], env->ep);
// 	}
// 	if ((n < env->ac - 1))
// 	{
// 		printf("Make new guy %d\n", n);
// 		proc(env, n + 1, pip, fork_cmd);
// 	}
// }