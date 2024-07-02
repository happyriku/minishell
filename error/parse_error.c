/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kai11 <kai11@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 17:26:06 by kai11             #+#    #+#             */
/*   Updated: 2024/06/24 17:29:54 by kai11            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_error(char *msg, t_token **rest, t_token *tok)
{
	syntax_error(msg);
	g_info.last_status = 1;
	while (tok && tok->kind != TK_EOF)
		tok++;
	*rest = tok;
}
