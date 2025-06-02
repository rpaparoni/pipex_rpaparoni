/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpaparon <rpaparon@student.42madrid.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:03:26 by rpaparon          #+#    #+#             */
/*   Updated: 2025/05/29 17:23:44 by rpaparon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>

int		main(int argc, char *argv[], char **envp);
void	ft_execpipe(int *fd, char *argv[], char **envp);
void	ft_kill(char *msg, int *fd);
void	first_child(char **argv, char **envp, int *fd);
void	second_child(char **argv, char **envp, int *fd);
void	free_array(char **cmd);
char	*find_path(char **envp, char *cmd);
void	ft_cmd(char **envp, char **cmd);
char	*ft_cmd_complete(char **paths, char *cmd1);
void	ft_error(char *msg);

#endif