/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpaparon <rpaparon@student.42madrid.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 16:10:34 by rpaparon          #+#    #+#             */
/*   Updated: 2025/02/27 19:02:50 by rpaparon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

void	ft_execpipe(int in_fd, int out_fd, char *argv[], char **envp)
{
	char	**cmd1;
	char	**cmd2;
	pid_t	pid;
	int		pipe_fd[2];

	if (pipe(pipe_fd) < 0)
	{
		perror("Error creating pipe");
		close_files(in_fd, out_fd);
		exit(EXIT_FAILURE);
	}
	pid = fork();
}

int	main(int argc, char *argv[], char **envp)
{
	int		in_fd;
	int		out_fd;

	if (argc != 5)
	{
		ft_printf("Usage: %s infile cmd1 cmd2 outfile\n", argv[0]);
		return (EXIT_FAILURE);
	}
	open_files(argv[1], argv[4], in_fd, out_fd);
	ft_execpipe(in_fd, out_fd, argv, envp);
	close_files(in_fd, out_fd);
	return (EXIT_SUCCESS);
}
