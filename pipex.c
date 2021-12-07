/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyamcha <tyamcha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 10:47:22 by tyamcha           #+#    #+#             */
/*   Updated: 2021/12/07 14:32:32 by tyamcha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int		dscr[2];
	pid_t	fork_res;
	
	// if (argc != 5)
	// 	error("Error\nUsage: ./pipex infile \"cmd1\" \"cmd2\" outfile");
	if (pipe(dscr) == -1)
		error("PIPE Error");
	fork_res = fork();
	if (fork_res == -1)
		error("FORK Error");
	else if (fork_res == 0)
	{
		close(dscr[0]);
		dup2(dscr[1], STDOUT_FILENO);
		printf("Child");
		exit(0);
	}
	else
	{
		char ch;
		int x;
		
		close(dscr[1]);
		wait(&fork_res);
		x = read(dscr[0], &ch, 1);
		while (x > 0 && ch > 0)
		{
			printf("%c\n", ch);
			x = read(dscr[0], &ch, 1);
		}
		printf("Parent\n");
		exit(1);
	}
	return (0);
}
