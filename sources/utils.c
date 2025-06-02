/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpaparon <rpaparon@student.42madrid.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 16:10:28 by rpaparon          #+#    #+#             */
/*   Updated: 2025/05/29 17:23:46 by rpaparon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*find_path(char **envp, char *cmd)
{
	int		i;
	char	**paths;
	char	*full_cmd;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	if (!envp[i])
		return (NULL);
	paths = ft_split(envp[i] + 5, ':');
	if (!paths)
		return (NULL);
	full_cmd = ft_cmd_complete(paths, cmd);
	free_array(paths);
	return (full_cmd);
}

void	ft_cmd(char **envp, char **cmd)
{
	char	*path;

	if (!cmd || !cmd[0])
		ft_error("Error: empty command");
	if (access(cmd[0], X_OK) == 0)
		path = cmd[0];
	else
		path = find_path(envp, cmd[0]);
	if (path == NULL)
	{
		ft_putstr_fd("Command not found: ", 2);
		ft_putstr_fd(cmd[0], 2);
		ft_putstr_fd("\n", 2);
		exit(127);
	}
	if (execve(path, cmd, envp) == -1)
		ft_error("execve error");
}

char	*ft_cmd_complete(char **paths, char *cmd1)
{
	int		i;
	char	*cut_paths;
	char	*real_path;

	i = 0;
	while (paths[i])
	{
		cut_paths = ft_strjoin(paths[i], "/");
		if (!cut_paths)
			return (NULL);
		real_path = ft_strjoin(cut_paths, cmd1);
		free(cut_paths);
		if (access(real_path, F_OK) == 0)
			return (real_path);
		free(real_path);
		i++;
	}
	return (NULL);
}

void	ft_error(char *msg)
{
	perror(msg);
	exit(1);
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
