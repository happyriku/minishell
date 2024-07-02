/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_heredoc_info.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkodaira <kkodaira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 19:46:23 by kkodaira          #+#    #+#             */
/*   Updated: 2024/06/26 20:22:13 by kkodaira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

void	read_heredoc(int pipe_fd[2], char *delimiter, bool delim_quoted)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (line == NULL || g_info.readline_interrupted == true
			|| strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		if (!delim_quoted)
			line = expand_heredoc_line(line);
		dprintf(pipe_fd[1], "%s\n", line);
		free(line);
	}
}

int	get_heredoc_inpipefd(char *delimiter, bool delim_quoted)
{
	int	pipe_fd[2];

	if (pipe(pipe_fd) < 0)
		fatal_error("pipe");
	g_info.readline_interrupted = false;
	read_heredoc(pipe_fd, delimiter, delim_quoted);
	close(pipe_fd[1]);
	if (g_info.readline_interrupted)
	{
		close(pipe_fd[0]);
		return (-1);
	}
	return (pipe_fd[0]);
}
