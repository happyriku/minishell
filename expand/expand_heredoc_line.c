/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc_line.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkodaira <kkodaira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 20:04:42 by kkodaira          #+#    #+#             */
/*   Updated: 2024/06/26 20:13:31 by kkodaira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_heredoc_line(char *line)
{
	char	*new_word;

	new_word = calloc(1, sizeof(char));
	if (new_word == NULL)
		fatal_error("calloc");
	while (*line)
	{
		if (is_env_name(line))
			expand_env_name(&new_word, &line, line);
		else if (is_exit_var(line))
			expand_exit_var(&new_word, &line, line);
		else
			append_char(&new_word, *(line++));
	}
	free(line);
	return (new_word);
}
