/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unix <unix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 12:46:46 by unix              #+#    #+#             */
/*   Updated: 2021/12/10 13:42:15 by unix             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*full_path(char *path, char *name)
{
	char *tmp;
	char *res;
	if (name[0] == '/')
		return (name);
	if (path[ft_strlen(path) - 1] != '/')
	{
		tmp = ft_strjoin(path, "/");
		res = ft_strjoin(tmp, name);
		free(tmp);
		return(res);
	}
	return (ft_strjoin(path, name));
}

void run(char *comand, char **envp)
{
	char **ac;
	char **path;
	int		i;

	i = 0;
	ac = ft_split(comand, ' ');
	while (*(envp[20])++ != '=')
		;
	path = ft_split(envp[20], ':');
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