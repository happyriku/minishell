/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kai11 <kai11@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 17:42:12 by kai11             #+#    #+#             */
/*   Updated: 2024/06/24 17:46:38 by kai11            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_node(t_node *node)
{
	if (node == NULL)
		return ;
	expand_node(node->next);
	expand_node(node->command);
	expand_node(node->redirects);
	expand_tok(node->args);
	expand_tok(node->filename);
}
