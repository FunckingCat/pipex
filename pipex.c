/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unix <unix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 10:47:22 by tyamcha           #+#    #+#             */
/*   Updated: 2021/12/07 20:35:55 by unix             ###   ########.fr       */
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
	int		dscr[2];
	pid_t	fork_cmd1;
	pid_t	fork_cmd2;

	// if (argc != 5)
	// 	error("Error\nUsage: ./pipex infile \"cmd1\" \"cmd2\" outfile");
	validate(argc - 1, argv + 1);
	// if (pipe(dscr) == -1)
	// 	error("PIPE Error");
	// fork_cmd1 = fork();
	// if (fork_cmd1 == -1)
	// 	error("FORK Error");
	// else if (fork_cmd1 == 0)
	// {
	// 	close(dscr[0]);
	// 	dup2(dscr[1], STDOUT_FILENO);
	// 	cmd1(0, NULL);
	// }

	// fork_cmd2 = fork();
	// if (fork_cmd2 == -1)
	// 	error("FORK Error");
	// else if (fork_cmd2 == 0)
	// {
	// 	close(dscr[1]);
	// 	dup2(dscr[0], STDIN_FILENO);
	// 	wait(&fork_cmd1);
	// 	cmd2(0, NULL);
	// }
	
	// close(dscr[1]);
	// wait(&fork_cmd1);
	// wait(&fork_cmd2);
	// printf("Parent\n");
	return (0);
}
