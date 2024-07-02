/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkodaira <kkodaira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 13:29:34 by kai11             #+#    #+#             */
/*   Updated: 2024/06/29 19:14:32 by kkodaira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipe_cpy(int dst[2], int src[2])
{
	dst[0] = src[0];
	dst[1] = src[1];
}

void	prepare_pipe(t_node *node)
{
	if (node->next == NULL)
		return ;
	if (pipe(node->outpipe) < 0)
		fatal_error("pipe");
	pipe_cpy(node->next->inpipe, node->outpipe);
}

void	prepare_pipe_child(t_node *node)
{
	close(node->outpipe[0]);
	dup2(node->inpipe[0], STDIN_FILENO);
	if (node->inpipe[0] != STDIN_FILENO)
		close(node->inpipe[0]);
	dup2(node->outpipe[1], STDOUT_FILENO);
	if (node->outpipe[1] != STDOUT_FILENO)
		close(node->outpipe[1]);
}

void	prepare_pipe_parent(t_node *node)
{
	if (node->inpipe[0] != STDIN_FILENO)
		close(node->inpipe[0]);
	if (node->next)
		close(node->outpipe[1]);
}
