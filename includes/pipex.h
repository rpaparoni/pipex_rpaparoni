/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpaparon <rpaparon@student.42madrid.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:03:26 by rpaparon          #+#    #+#             */
/*   Updated: 2025/03/13 15:16:24 by rpaparon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H

# define PIPEX_H

# include "../libft/libft.h"

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>

int		main(int argc, char *argv[], char **envp);
void	ft_execpipe(int in_fd, int out_fd, char *argv[], char **envp);
void	open_files(char *infile, char *outfile, int *in_fd, int *out_fd);
void	ft_error(char *msg, int *fd1, int *fd2);
void	child_process(int in_fd, int pipe_fd[], char *cmd[], char **envp);
void	parent_process(int pipe_fd[], int out_fd, char *cmd[], char **envp);
char	*find_path(char *cmd, char **envp);

//bonus
void	execute_command(char *cmd, char **envp, int infile, int outfile);
void	child_pipe_process(char *argv, char **envp);

#endif