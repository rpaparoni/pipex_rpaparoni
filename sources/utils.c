/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpaparon <rpaparon@student.42madrid.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 16:10:28 by rpaparon          #+#    #+#             */
/*   Updated: 2025/02/28 14:16:57 by rpaparon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	int		i;
	char	*part_path;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
	return (0);
}

void	error(char *msg, int *fd1, int *fd2)
{
	perror(msg);
	if (fd1 && *fd1 >= 0)
		close(*fd1);
	if (fd2 && *fd2 >= 0)
		close(*fd2);
	exit(EXIT_FAILURE);
}

void	close_files(int *in_fd, int *out_fd)
{
	close(*in_fd);
	close(*out_fd);
}

void	open_files(char *infile, char *outfile, int *in_fd, int *out_fd)
{
	*in_fd = open(infile, O_RDONLY);
	if (*in_fd < 0)
	{
		perror("Error opening infile");
		exit(EXIT_FAILURE);
	}
	*out_fd = open(outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (*out_fd < 0)
	{
		perror("Error opening outfile");
		close(*in_fd);
		exit(EXIT_FAILURE);
	}
}
