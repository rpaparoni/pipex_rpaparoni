/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpaparon <rpaparon@student.42madrid.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 12:15:23 by rpaparon          #+#    #+#             */
/*   Updated: 2025/03/03 19:49:17 by rpaparon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void execute_command(char *cmd, char **envp, int infile, int outfile)
{
    char	**cmd_args;
    char	*path_cmd;

    cmd_args = ft_split(cmd, ' ');
    path_cmd = find_path(cmd_args[0], envp);
    if (!path_cmd)
        error("Command not found", &infile, &outfile);

    if (fork() == 0) // Crear un proceso hijo para ejecutar el comando
    {
        dup2(infile, STDIN_FILENO);
        dup2(outfile, STDOUT_FILENO);
        close(infile);
        close(outfile);
        execve(path_cmd, cmd_args, envp);
        error("Error executing command", NULL, NULL); // Si llega aquí, execve falló
    }
    free(path_cmd);
    free(cmd_args); // Liberar memoria
}

void here_doc(char *limiter)
{
    int		fd[2];
    char	*line;

    if (pipe(fd) == -1)
        error("Pipe failed", NULL, NULL);

    while (1)
    {
        ft_putstr_fd("here_doc> ", STDOUT_FILENO);
        line = get_next_line(STDIN_FILENO);
        if (!line) // 🔴 Si llega EOF, salimos
            break;
        if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0 && line[ft_strlen(limiter)] == '\n')
        {
            free(line);
            break;
        }
        ft_putstr_fd(line, fd[1]);
        free(line);
    }
    close(fd[1]); // 🔴 IMPORTANTE: Cerrar escritura antes de duplicar
    dup2(fd[0], STDIN_FILENO);
    close(fd[0]); // 🔴 Cerrar lectura después de duplicar
}


void exec_more_pipes(int argc, char *argv[], char **envp, int infile, int outfile)
{
    int	i;
    int	pipe_fd[2];
    int	prev_pipe = infile;

    i = 2;
    while (i < argc - 2)
    {
        if (pipe(pipe_fd) == -1)
            error("Pipe failed", &prev_pipe, NULL);

        if (fork() == 0) // Crear un proceso hijo para cada comando
        {
            close(pipe_fd[0]); // Cerrar el extremo de lectura del pipe
            dup2(prev_pipe, STDIN_FILENO);
            dup2(pipe_fd[1], STDOUT_FILENO);
            close(prev_pipe);
            close(pipe_fd[1]);
            execute_command(argv[i], envp, STDIN_FILENO, STDOUT_FILENO);
        }
	close(prev_pipe);
        close(pipe_fd[1]);
        prev_pipe = pipe_fd[0]; // El siguiente comando leerá de este pipe
        i++;
    }
    dup2(prev_pipe, STDIN_FILENO);
    dup2(outfile, STDOUT_FILENO);
    close(prev_pipe);
    execute_command(argv[i], envp, STDIN_FILENO, outfile);
}

int	main(int argc, char *argv[], char **envp)
{
    int	infile;
    int	outfile;

    if (argc >= 5)
    {
        if (ft_strncmp(argv[1], "here_doc", 8) == 0)
        {
            outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (outfile < 0)
                error("Error opening output file", NULL, NULL);
            here_doc(argv[2]);
        }
        else
        {
            infile = open(argv[1], O_RDONLY);
            if (infile < 0)
                error("Error opening input file", NULL, NULL);
            outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (outfile < 0)
                error("Error opening output file", &infile, NULL);
            dup2(infile, STDIN_FILENO);
        }
        exec_more_pipes(argc, argv, envp, STDIN_FILENO, outfile);
    }
    else
        error("Usage: ./pipex file1 cmd1 cmd2 ... file2", NULL, NULL);
    return (0);
}

