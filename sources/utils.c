/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpaparon <rpaparon@student.42madrid.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 16:10:28 by rpaparon          #+#    #+#             */
/*   Updated: 2025/03/13 15:01:32 by rpaparon         ###   ########.fr       */
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

void	ft_error(char *msg, int *fd1, int *fd2)
{
	ft_printf(msg);
	if (fd1 && *fd1 >= 0)
		close(*fd1);
	if (fd2 && *fd2 >= 0)
		close(*fd2);
	exit(EXIT_FAILURE);
}

void	open_files(char *infile, char *outfile, int *in_fd, int *out_fd)
{
	*in_fd = open(infile, O_RDONLY);
	if (*in_fd < 0)
	{
		ft_error("Error opening infile", NULL, NULL);
		exit(EXIT_FAILURE);
	}
	*out_fd = open(outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (*out_fd < 0)
	{
		ft_error("Error opening outfile", in_fd, NULL);
		exit(EXIT_FAILURE);
	}
}
