/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyamcha <tyamcha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 12:46:46 by unix              #+#    #+#             */
/*   Updated: 2021/12/11 13:15:30 by tyamcha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*full_path(char *path, char *name)
{
	char	*tmp;
	char	*res;

	if (name[0] == '/')
		return (name);
	if (path[ft_strlen(path) - 1] != '/')
	{
		tmp = ft_strjoin(path, "/");
		res = ft_strjoin(tmp, name);
		free(tmp);
		return (res);
	}
	return (ft_strjoin(path, name));
}

void	run(char *comand, char **envp)
{
	char	**ac;
	char	**path;
	int		i;
	int		j;

	i = 0;
	j = 0;
	ac = ft_split(comand, ' ');
	while (ft_strncmp("PATH", envp[j], 4))
		j++;
	while (*(envp[j]) != '=')
		envp[j]++;
	envp[j]++;
	path = ft_split(envp[j], ':');
	while (path[i] != NULL)
	{
		execve(full_path(path[i], ac[0]), ac, envp);
		i++;
	}
	error(ac[0], "command not found");
}

void	close_descriptors(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->cmds)
	{
		if (env->commands[i].in != 0)
			close(env->commands[i].in);
		if (env->commands[i].out != 1)
			close(env->commands[i].out);
		i++;
	}
}

void	exec(t_command *cmd, t_env *env)
{
	if (dup2(cmd->in, 0) == -1 || dup2(cmd->out, 1) == -1)
		error("dup2", "dup failed");
	close_descriptors(env);
	run(cmd->arg, env->ep);
}

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
			exec(&env->commands[i], env);
		i++;
	}
}
