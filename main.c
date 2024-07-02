/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kai11 <kai11@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 20:25:29 by kkodaira          #+#    #+#             */
/*   Updated: 2024/06/30 19:06:33 by kai11            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

t_info	g_info = {};

void	interpret(char *line)
{
	t_token	*tok;
	t_node	*node;

	tok = tokenize(line);
	if (g_info.syntax_error == true)
		g_info.last_status = TOKENIZE_ERROR;
	else
	{
		node = parse(tok);
		if (g_info.syntax_error)
			g_info.last_status = PARSE_ERROR;
		else
		{
			expand(node);
			g_info.last_status = exec(node);
		}
	}
}

int	main(void)
{
	char	*line;

	rl_outstream = stderr;
	env_init();
	setup_signal();
	while (1)
	{
		line = readline("minishell$ ");
		if (line == NULL)
			break ;
		if (*line)
			add_history(line);
		interpret(line);
		free(line);
	}
	exit(g_info.last_status);
}
