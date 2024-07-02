/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkodaira <kkodaira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 19:23:27 by kkodaira          #+#    #+#             */
/*   Updated: 2024/06/29 19:47:16 by kkodaira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_redirect(t_node *node)
{
	if (node->kind == ND_REDIRECT_APPEND)
		return (true);
	else if (node->kind == ND_REDIRECT_HEREDOC)
		return (true);
	else if (node->kind == ND_REDIRECT_IN)
		return (true);
	else if (node->kind == ND_REDIRECT_OUT)
		return (true);
	else
		return (false);
}

int	stashfd(int fd)
{
	int	stashfd;

	stashfd = fcntl(fd, F_DUPFD, 10);
	if (stashfd < 0)
		fatal_error("fcntl");
	if (close(fd) < 0)
		fatal_error("close");
	return (stashfd);
}

void	do_redirect(t_node *redirects)
{
	if (redirects == NULL)
		return ;
	if (is_redirect(redirects))
	{
		redirects->stashed_targetfd = stashfd(redirects->targetfd);
		dup2(redirects->filefd, redirects->targetfd);
	}
	else
		assert_error("do_redirect");
	do_redirect(redirects->next);
}

void	reset_redirect(t_node *redirects)
{
	if (redirects == NULL)
		return ;
	reset_redirect(redirects->next);
	if (is_redirect(redirects))
	{
		close(redirects->filefd);
		close(redirects->targetfd);
		dup2(redirects->stashed_targetfd, redirects->targetfd);
	}
	else
		assert_error("reset_redirect");
}
