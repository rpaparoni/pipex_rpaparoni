/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpaparon <rpaparon@student.42madrid.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 16:10:28 by rpaparon          #+#    #+#             */
/*   Updated: 2025/05/28 16:00:40 by rpaparon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*find_path(char *cmd, char **envp)
{
	int		i;
	char	**paths;
	char	*full_cmd;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			break;
		i++;
	}
	if (!envp[i])
		return (NULL);
	paths = ft_split(envp[i] + 5, ':');
	if (!paths)
		return (NULL);
	full_cmd = ft_cmd_complete(paths, cmd);
	free_array(paths); // libera split después de generar el path final
	return (full_cmd);
}

char	*ft_cmd_complete(char **paths, char *cmd)
{
	char	*path;
	char	*tmp;
	int		i;

	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}

void	ft_error(char *msg, int *fd1, int *fd2)
{
	ft_printf("%s\n", msg);
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

void	free_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
		free(array[i++]);
	free(array);
}
