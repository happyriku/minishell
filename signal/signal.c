/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkodaira <kkodaira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 17:31:06 by kkodaira          #+#    #+#             */
/*   Updated: 2024/06/29 18:21:52 by kkodaira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_state(void)
{
	if (g_info.signal == 0)
		return (0);
	else if (g_info.signal == SIGINT)
	{
		g_info.signal = 0;
		g_info.readline_interrupted = true;
		rl_replace_line("", 0);
		rl_done = 1;
		return (0);
	}
	return (0);
}

void	reset_signal(void)
{
	reset_sig(SIGINT);
	reset_sig(SIGQUIT);
}

void	setup_signal(void)
{
	extern int	_rl_echo_control_chars;

	_rl_echo_control_chars = 0;
	if (isatty(STDIN_FILENO))
		rl_event_hook = check_state;
	ignore_sig(SIGQUIT);
	handle_sig(SIGINT);
}
