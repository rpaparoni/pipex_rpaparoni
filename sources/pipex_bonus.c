/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpaparon <rpaparon@student.42madrid.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 12:15:23 by rpaparon          #+#    #+#             */
/*   Updated: 2025/03/05 13:41:59 by rpaparon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	open_file(char *argv, int i)
{
	int	file;

	file = 0;
	if (i == 0)
		file = open(argv, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else if (i == 1)
		file = open(argv, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (i == 2)
		file = open(argv, O_RDONLY, 0777);
	if (file == -1)
		error("error opening file", NULL, NULL);
	return (file);
}

void	child_pipe_process(char *argv, char **envp)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		error("error making pipe", NULL, NULL);
	pid = fork();
	if (pid == -1)
		error("error making pipe", NULL, NULL);
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		execute(argv, envp);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(pid, NULL, 0);
	}
}

/* Function who make a child process that will read from the stdin with
 get_next_line until it find the limiter word and then put the output inside a
 pipe. The main process will change his stdin for the pipe file descriptor. */
 void	here_doc(char *limiter, int argc)
 {
	 pid_t	reader;
	 int		fd[2];
	 char	*line;
 
	 if (argc < 6)
		 usage();
	 if (pipe(fd) == -1)
		 error("error making pipe", NULL, NULL);
	 reader = fork();
	 if (reader == -1)
		 error("error forking process", NULL, NULL);
	 if (reader == 0) // Proceso hijo (lee entrada)
	 {
		 close(fd[0]); // Cierra lectura del pipe
		 while ((line = get_next_line(STDIN_FILENO)))
		 {
			 if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0 && line[ft_strlen(limiter)] == '\n')
			 {
				 free(line);
				 exit(EXIT_SUCCESS);
			 }
			 write(fd[1], line, ft_strlen(line));
			 free(line);
		 }
		 exit(EXIT_SUCCESS);
	 }
	 else // Proceso padre
	 {
		 close(fd[1]); // Cierra escritura del pipe
		 dup2(fd[0], STDIN_FILENO);
		 close(fd[0]); // Cierra lectura después de duplicar
		 wait(NULL);
	 }
 }

/* Main function that run the childs process with the right file descriptor
 or display an error message if arguments are wrong. It will run here_doc
 function if the "here_doc" string is find in argv[1] */
int	main(int argc, char **argv, char **envp)
{
	int	i;
	int	filein;
	int	fileout;

	if (argc >= 5)
	{
		if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		{
			i = 3;
			fileout = open_file(argv[argc - 1], 0);
			here_doc(argv[2], argc);
		}
		else
		{
			i = 2;
			fileout = open_file(argv[argc - 1], 1);
			filein = open_file(argv[1], 2);
			dup2(filein, STDIN_FILENO);
		}
		while (i < argc - 2)
			child_pipe_process(argv[i++], envp);
		dup2(fileout, STDOUT_FILENO);
		execute(argv[argc - 2], envp);
	}
    ft_printf("Usage: %s infile cmd1 cmd2 outfile\n", argv[0]);
}

