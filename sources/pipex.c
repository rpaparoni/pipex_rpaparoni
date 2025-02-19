/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpaparon <rpaparon@student.42madrid.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 16:10:34 by rpaparon          #+#    #+#             */
/*   Updated: 2025/02/18 21:09:44 by rpaparon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

int main(int argc, char *argv[]) {
    
    int in_fd;
    char *a;
    char *b;

    if (argc != 5) {
        ft_printf("Usage: %s infile cmd1 cmd2 outfile\n", argv[0]);
        return EXIT_FAILURE;
    }

    in_fd = open(argv[1], O_RDONLY);

    if (in_fd < 0) {
        perror("Error opening infile");
        return EXIT_FAILURE;
    }
    a = argv[2];
    b = argv[3];
    ft_execpipe(a, b);
    close(in_fd);

    return EXIT_SUCCESS;
}

int ft_execpipe(char *a, char *b)
{
    if (execlp(a, a, b, (char *)NULL) == -1) {
        perror("execlp error");
        exit(EXIT_FAILURE);
    }
    return (0);
}
