/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kai11 <kai11@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 13:12:27 by kai11             #+#    #+#             */
/*   Updated: 2024/06/24 14:51:40 by kai11            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

void	tokenize_error(char *msg, char **rest, char *line)
{
	syntax_error(msg);
	g_info.last_status = 1;
	while (*line != '\0')
		line++;
	*rest = line;
}
