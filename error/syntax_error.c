/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kai11 <kai11@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 13:15:06 by kai11             #+#    #+#             */
/*   Updated: 2024/06/24 16:27:24 by kai11            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

void	syntax_error(char *msg)
{
	dprintf(STDERR_FILENO, "syntax error: %s\n", msg);
	g_info.syntax_error = true;
}
