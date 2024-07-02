/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kai11 <kai11@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 12:21:04 by kai11             #+#    #+#             */
/*   Updated: 2024/06/29 12:56:14 by kai11            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <ctype.h>

bool	is_numeric(char *str)
{
	while (*str)
	{
		if (!isdigit(*str))
			return (false);
		str++;
	}
	return (true);
}

int	builtin_exit(char **argv)
{
	if (argv[2])
	{
		syntax_error("exit");
		return (1);
	}
	if (argv[1] == NULL)
	{
		exit (g_info.last_status);
	}
	if (argv[1])
	{
		if (is_numeric(argv[1]))
			exit ((int)(argv[1] - '0'));
		else
		{
			syntax_error("exit");
			exit (255);
		}
	}
	assert_error("builtin exit");
}
