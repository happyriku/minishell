/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_exit_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kai11 <kai11@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 14:47:53 by kai11             #+#    #+#             */
/*   Updated: 2024/06/25 15:04:17 by kai11            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_exit_var(char *word)
{
	if (*word == NULL || *(word + 1) == NULL)
		return (false);
	return (*word == '$' && *(word + 1) == '?');
}

void	expand_exit_var(char **dst, char **rest, char *word)
{
	if (*word != '$')
		assert_error("expand exit var");
	word++;
	if (*word != '?')
		assert_error("expand exit var");
	word++;
	append_char(dst, g_info.last_status + '0');
	*rest = word;
}
