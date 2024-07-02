/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkodaira <kkodaira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 13:31:49 by kai11             #+#    #+#             */
/*   Updated: 2024/06/29 20:30:52 by kkodaira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

void	assert_error(char *msg)
{
	dprintf(STDERR_FILENO, "assert error: %s\n", msg);
	exit (1);
}

void	fatal_error(char *msg)
{
	dprintf(STDERR_FILENO, "fatal error: %s\n", msg);
	exit (1);
}

void	err_exit(const char *location, const char *msg, int status)
{
	dprintf(STDERR_FILENO, "%s: %s\n", location, msg);
	exit(status);
}
