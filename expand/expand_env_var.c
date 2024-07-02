/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kai11 <kai11@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 18:32:32 by kai11             #+#    #+#             */
/*   Updated: 2024/06/25 15:36:04 by kai11            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <ctype.h>

bool	is_alpha_under(char c)
{
	return (isalpha(c) || c == '_');
}

bool	is_alpha_num_under(char c)
{
	return (is_alpha_under(c) || isdigit(c));
}

bool	is_env_name(char *word)
{
	if (*word == NULL || *(word + 1) == NULL)
		return (false);
	return (*word == '$' && is_alpha_under(*(word + 1)));
}

void	expand_env_name(char **dst, char **rest, char *word)
{
	char	*name;
	char	*value;

	if (*word != '$')
		assert_error("expand env name");
	word++;
	name = calloc(1, sizeof(char));
	if (name == NULL)
		fatal_error("calloc");
	while (is_alpha_num_under(*word))
	{
		append_char(&name, *word);
		word++;
	}
	value = get_value_from_name(g_info.envmap, name);
	if (value == NULL)
		*dst = NULL;
	else
	{
		while (*value)
		{
			append_char(dst, *value);
			value++;
		}
	}
	free(name);
	*rest = word;
}
