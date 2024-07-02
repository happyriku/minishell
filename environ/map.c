/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kai11 <kai11@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 13:22:48 by kai11             #+#    #+#             */
/*   Updated: 2024/06/30 16:17:01 by kai11            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>

void divide_to_name_value(char *environ, char **name, char **value)
{
	size_t i;

	i = 0;
	while (environ[i] != '\0' && environ[i] != '=')
		i++;
	if (environ[i] == '\0')
	{
		*name = strdup(environ);
		*value = NULL;
	}
	else
	{
		*name = strndup(environ, i);
		*value = strdup(environ + i + 1);
	}
	return ;
}

void map_make(t_envmap *map, char *environ, bool allow_null_value)
{
	char *name;
	char *value;

	divide_to_name_value(environ, &name, &value);
	if (allow_null_value == false && value == NULL)
		return;
	map_set(map, name, value);
}

char *get_value_from_name(t_envmap *map, char *name)
{
	t_envvar	*envvar;
	char		*value;

	envvar = map->envvar_dummy_head.next;
	while (envvar)
	{
		if (strcmp(envvar->name, name) == 0)
		{
			if (envvar->is_exported)
			{
				value = strdup(envvar->value);
				if (value == NULL)
					fatal_error("strdup");
				return (value);
			}
			else
				return (NULL);
		}
		envvar = envvar->next;
	}
	return (NULL);
}

t_envvar	*get_envvar_from_name(t_envmap *map, char *name)
{
	t_envvar	*cur;

	cur = map->envvar_dummy_head.next;
	while (cur)
	{
		if (strcmp(cur->name, name) == 0)
			return (cur);
		cur = cur->next;
	}
	return (NULL);
}

void	map_unset(t_envmap *map, char *name)
{
	t_envvar	*envvar;
	t_envvar	*pre_envvar;
	t_envvar	*tmp;

	envvar = map->envvar_dummy_head.next;
	if (strcmp(envvar->name, name) == 0)
	{
		free(envvar->name);
		if (envvar->value)
			free(envvar->value);
		tmp = envvar->next;
		free(envvar);
		map->envvar_dummy_head.next = tmp;
		return ;
	}
	pre_envvar = envvar;
	envvar = envvar->next;
	while (envvar)
	{
		if (strcmp(envvar->name, name) == 0)
		{
			free(envvar->name);
			if (envvar->value)
				free(envvar->value);
			free(envvar);
			tmp = envvar->next;
			pre_envvar->next = tmp;
			return ;
		}
		pre_envvar = envvar;
		envvar = envvar->next;
	}
	return ;
}
