/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpaparon <rpaparon@student.42madrid.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 16:10:28 by rpaparon          #+#    #+#             */
/*   Updated: 2025/02/27 19:04:36 by rpaparon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	close_files(int in_fd, int out_fd)
{
	close(in_fd);
	close(out_fd);
}

void	open_files(char *infile, char *outfile, int in_fd, int out_fd)
{
	in_fd = open(infile, O_RDONLY);
	if (in_fd < 0)
	{
		perror("Error opening infile");
		exit(EXIT_FAILURE);
	}
	out_fd = open(outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (out_fd < 0)
	{
		perror("Error opening outfile");
		close(in_fd);
		exit(EXIT_FAILURE);
	}
}
