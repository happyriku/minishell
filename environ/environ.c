/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kai11 <kai11@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 20:39:55 by kkodaira          #+#    #+#             */
/*   Updated: 2024/06/30 17:05:22 by kai11            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*make_environ_str(char *name, char *value)
{
	char	*str;

	str = calloc(1, sizeof(char));
	if (str == NULL)
		fatal_error("calloc");
	while (*name)
		append_char(&str, *(name++));
	append_char(&str, '=');
	while (*value)
		append_char(&str, *(value++));
	append_char(&str, '\0');
	return (str);
}

size_t	environ_len(t_envmap *map)
{
	size_t	len;
	t_envvar	*cur;

	len = 0;
	cur = map->envvar_dummy_head.next;
	while (cur)
	{
		cur = cur->next;
		len++;
	}
	return (len);
}

char	**get_environ(t_envmap *map)
{
	t_envvar	*cur;
	char		**environ;
	size_t		i;

	cur = map->envvar_dummy_head.next;
	i = 0;
	environ = malloc(sizeof(char *) * (environ_len(map) + 1));
	while (cur)
	{
		if (cur->is_exported == true && cur->value)
		{
			environ[i] = make_environ_str(cur->name, cur->value);
			i++;
		}
		cur = cur->next;
	}
	environ[i] = NULL;
	return (environ);
}
