/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpaparon <rpaparon@student.42madrid.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 16:10:28 by rpaparon          #+#    #+#             */
/*   Updated: 2025/02/27 23:45:26 by rpaparon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static char	**get_paths_from_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (ft_split(envp[i] + 5, ':'));
		i++;
	}
	return (NULL);
}

char	*find_path(char *cmd, char **envp)
{
	int		i;
	char	*full_cmd;
	char	**paths;

	if (!cmd || !envp)
		return (NULL);
	paths = get_paths_from_env(envp);
	if (!paths)
		return (NULL);
	i = -1;
	while (paths[++i])
	{
		full_cmd = ft_strjoin3(paths[i], "/", cmd);
		if (access(full_cmd, X_OK) == 0)
			return (ft_free_strarr(paths), full_cmd);
		free(full_cmd);
	}
	return (ft_free_strarr(paths), NULL);
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
