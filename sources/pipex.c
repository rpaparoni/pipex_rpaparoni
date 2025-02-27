/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpaparon <rpaparon@student.42madrid.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 16:10:34 by rpaparon          #+#    #+#             */
/*   Updated: 2025/02/27 23:52:30 by rpaparon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_execpipe(int in_fd, int out_fd, char *argv[], char **envp)
{
    char    **cmd1;
    char    **cmd2;
    pid_t   pid;
    int     pipe_fd[2];
    
    if (pipe(pipe_fd) < 0)
    {
        error("Error creating pipe", &in_fd, &out_fd);
    }
    pid = fork();
    if (pid == 0)
    {
        cmd1 = ft_split(argv[2], ' ');
        child_process(in_fd, pipe_fd, cmd1, envp);
    }
    else if (pid > 0)
    {
        cmd2 = ft_split(argv[3], ' ');
        parent_process(pipe_fd, out_fd, cmd2, envp);
    }
    else
    {
        error("Error forking process", &in_fd, &out_fd);
    }
}
void	child_process(int in_fd, int pipe_fd[], char *cmd[], char **envp)
{
	char *path_cmd;

	dup2(in_fd, STDIN_FILENO);
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[0]);

	path_cmd = find_path(cmd[0], envp);
	if (!path_cmd)
		error(NULL, NULL, NULL);
	execve(path_cmd, cmd, envp);
	error(NULL, NULL, NULL);
}

void	parent_process(int pipe_fd[], int out_fd, char *cmd[], char **envp)
{
	char *path_cmd;

	dup2(pipe_fd[0], STDIN_FILENO);
	dup2(out_fd, STDOUT_FILENO);
	close(pipe_fd[1]);

	path_cmd = find_path(cmd[0], envp);
	if (!path_cmd)
		error(NULL, NULL, NULL);
	execve(path_cmd, cmd, envp);
	error(NULL, NULL, NULL);
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
    open_files(argv[1], argv[4], &in_fd, &out_fd);
    ft_execpipe(in_fd, out_fd, argv, envp);
    close_files(&in_fd, &out_fd);
    return (EXIT_SUCCESS);
}
