/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpaparon <rpaparon@student.42madrid.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 16:10:34 by rpaparon          #+#    #+#             */
/*   Updated: 2025/05/29 17:24:02 by rpaparon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_execpipe(int *fd, char *argv[], char **envp)
{
	pid_t	pid;
	pid_t	pid2;

	pid = fork();
	if (pid == -1)
		ft_kill("Error Fork", fd);
	if (pid == 0)
	{
		close(fd[0]);
		first_child(argv, envp, fd);
	}
	pid2 = fork();
	if (pid2 == -1)
		ft_kill("Error Fork", fd);
	if (pid2 == 0)
	{
		close(fd[1]);
		second_child(argv, envp, fd);
	}
	waitpid(pid, 0, 0);
	waitpid(pid2, 0, 0);
}

void	first_child(char **argv, char **envp, int *fd)
{
	int		file1_fd;
	char	**cmd1;

	file1_fd = open(argv[1], O_RDONLY);
	if (file1_fd == -1)
		ft_error("./pipex");
	dup2(file1_fd, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(file1_fd);
	close(fd[0]);
	close(fd[1]);
	cmd1 = ft_split(argv[2], ' ');
	if (!cmd1 || !cmd1[0])
		ft_error("Error command");
	ft_cmd(envp, cmd1);
	free_array(cmd1);
}

void	second_child(char **argv, char **envp, int *fd)
{
	int		file2_fd;
	char	**cmd2;

	file2_fd = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (file2_fd == -1)
		ft_error("./pipex");
	dup2(fd[0], STDIN_FILENO);
	dup2(file2_fd, STDOUT_FILENO);
	close(file2_fd);
	close(fd[0]);
	close(fd[1]);
	cmd2 = ft_split(argv[3], ' ');
	if (!cmd2 || !cmd2[0])
		ft_error("Error command");
	ft_cmd(envp, cmd2);
	free_array(cmd2);
}

void	ft_kill(char *msg, int *fd)
{
	if (msg != NULL)
		perror(msg);
	if (fd[0] >= 0)
		close(fd[0]);
	if (fd[1] >= 0)
		close(fd[1]);
	exit(EXIT_FAILURE);
}

int	main(int argc, char *argv[], char **envp)
{
	int		fd[2];

	if (argc != 5)
	{
		ft_printf("Usage: %s infile cmd1 cmd2 outfile\n", argv[0]);
		return (1);
	}
	if (pipe(fd) == -1)
		ft_error("Error Creating Pipe");
	ft_execpipe(fd, argv, envp);
	return (0);
}
