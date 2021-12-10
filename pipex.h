/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unix <unix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 10:47:27 by tyamcha           #+#    #+#             */
/*   Updated: 2021/12/10 13:47:26 by unix             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/wait.h>
# include "./libft/libft.h"

typedef struct s_command
{
	char	*arg;
	int		in;
	int		out;
}	t_command;

typedef struct s_env
{
	int			cmds;
	t_command	*commands;
	char		**ep;
	pid_t		*pids;
}	t_env;

t_env	*make_env(int argc, char **argv, char **envp);

void	error(char *name, char *desc);
void	open_descriptors(int ac, char **av, int *arr);
void	ft_putstr_fd(char *s, int fd);
char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);
void	fork_proc(t_env *env);
void	exec(t_command *cmd, t_env *env);

#endif