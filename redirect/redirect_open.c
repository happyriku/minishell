/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_open.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkodaira <kkodaira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 19:17:41 by kkodaira          #+#    #+#             */
/*   Updated: 2024/06/26 20:23:17 by kkodaira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	openfd(t_node *redirects)
{
	if (redirects->kind == ND_REDIRECT_IN)
		return (open(redirects->filename->word, O_RDONLY));
	else if (redirects->kind == ND_REDIRECT_OUT)
		return (open(redirects->filename->word,
			O_CREAT | O_WRONLY | O_TRUNC, 0644));
	else if (redirects->kind == ND_REDIRECT_APPEND)
		return (open(redirects->filename->word,
			O_CREAT | O_WRONLY | O_APPEND, 0644));
	else if (redirects->kind == ND_REDIRECT_HEREDOC)
		return (get_heredoc_inpipefd(redirects->delimiter->word, redirects->delim_quoted));
	else
		assert_error("openfd");
}

int	open_files(t_node *node)
{
	if (node == NULL || node->kind == ND_EOF)
		return (0);
	if (node->kind == ND_PIPELINE)
	{
		if (open_files(node->command) < 0)
			return (-1);
		if (open_files(node->next) < 0)
			return (-1);
		return (0);
	}
	else if (node->kind == ND_COMMAND)
		return (open_files(node->redirects));
	node->filefd = openfd(node);
}
