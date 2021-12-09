/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unix <unix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 10:47:22 by tyamcha           #+#    #+#             */
/*   Updated: 2021/12/09 18:35:20 by unix             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*full_path(char *path, char *name)
{
	char *tmp;
	char *res;
	
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
	exit(EXIT_FAILURE);
}

int	main(int argc, char **argv, char **envp)
{
	int		pip[2];
	int		inout[2];
	int		status1;
	int		status2;
	pid_t	fork_cmd1;
	pid_t	fork_cmd2;

	if (argc != 5)
		error("usage", "file1 cmd1 cmd2 file2");
		
	open_descriptors(argc - 1, argv + 1, inout);

	if (pipe(pip) == -1)
		error("pipe", "failed create a pipe");
	fork_cmd1 = fork();
	if (fork_cmd1 == -1)
		error("fork", "fork failed");
	else if (fork_cmd1 == 0)
	{
		close(pip[0]);
		dup2(inout[0], STDIN_FILENO);
		dup2(pip[1], STDOUT_FILENO);
		run(argv[2], envp);
	}

	fork_cmd2 = fork();
	if (fork_cmd2 == -1)
		error("fork", "fork failed");
	else if (fork_cmd2 == 0)
	{
		close(pip[1]);
		dup2(pip[0], STDIN_FILENO);
		dup2(inout[1], STDOUT_FILENO);
		wait(&fork_cmd1);
		run(argv[3], envp);
	}
	
	close(pip[1]);
	//close(inout[0]);
	//close(inout[1]);
	waitpid(fork_cmd1, &status1, 0);
	waitpid(fork_cmd2, &status2, 0);
	if (status1 || status2)
	{
        printf("Error\n");
    }
    else
	{
        printf("Exited Normally\n");
    }
	printf("Parent %d %d\n", status1, status2);
	return (0);
}
