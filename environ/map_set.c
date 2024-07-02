/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkodaira <kkodaira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 13:43:03 by kai11             #+#    #+#             */
/*   Updated: 2024/06/29 17:25:20 by kkodaira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>

t_envvar	*new_envvar(void)
{
	t_envvar	*new;

	new = calloc(1, sizeof(t_envvar));
	if (new == NULL)
		fatal_error("calloc");
	new->next = NULL;
	return (new);
}

void	value_update(t_envvar *envvar, char *value)
{
	char	*tmp;

	tmp = envvar->value;
	if (envvar->is_exported == true && tmp != NULL)
		free(tmp);
	envvar->value = value;
}

void	append_envvar(t_envmap *map, t_envvar *envvar)
{
	t_envvar	*cur;

	cur = map->envvar_dummy_head.next;
	while (cur)
		cur = cur->next;
	cur = envvar;
	cur->next = NULL;
}

void	map_set(t_envmap *map, char *name, char *value)
{
	t_envvar	*envvar;

	envvar = get_envvar_from_name(map, name);
	if (envvar)
	{
		value_update(envvar, value);
		return ;
	}
	envvar = new_envvar();
	if (value == NULL)
		envvar->is_exported = false;
	else
		envvar->is_exported = true;
	envvar->name = name;
	envvar->value = value;
	envvar->next = map->envvar_dummy_head.next;
	map->envvar_dummy_head.next = envvar;
	return ;
}
