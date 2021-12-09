/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unix <unix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 10:47:22 by tyamcha           #+#    #+#             */
/*   Updated: 2021/12/09 15:26:37 by unix             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	cmd1(int f1, char *cmd)
{
	printf("Child");
	exit(EXIT_SUCCESS);
}

void	cmd2(int f2, char *cmd)
{
	char	ch;
	int		x;

	x = read(0, &ch, 1);
	while (x > 0 && ch > 0)
	{
		printf("%c\n", ch);
		x = read(0, &ch, 1);
	}
	exit(EXIT_SUCCESS);
}

int	main(int argc, char **argv, char **envp)
{
	int		pip[2];
	int		inout[2];
	pid_t	fork_cmd1;
	pid_t	fork_cmd2;

	if (argc != 5)
		error("Error\nUsage: ./pipex infile \"cmd1\" \"cmd2\" outfile");
		
	open_descriptors(argc - 1, argv + 1, inout);
	
	// if (pipe(pip) == -1)
	// 	error("PIPE Error");
	// fork_cmd1 = fork();
	// if (fork_cmd1 == -1)
	// 	error("FORK Error");
	// else if (fork_cmd1 == 0)
	// {
	// 	close(pip[0]);
	// 	dup2(pip[1], STDOUT_FILENO);
	// 	cmd1(0, NULL);
	// }

	// fork_cmd2 = fork();
	// if (fork_cmd2 == -1)
	// 	error("FORK Error");
	// else if (fork_cmd2 == 0)
	// {
	// 	close(pip[1]);
	// 	dup2(pip[0], STDIN_FILENO);
	// 	wait(&fork_cmd1);
	// 	cmd2(0, NULL);
	// }
	
	// close(pip[1]);
	// wait(&fork_cmd1);
	// wait(&fork_cmd2);
	// printf("Parent\n");
	return (0);
}
