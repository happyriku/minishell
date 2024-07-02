/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kai11 <kai11@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 12:31:46 by kai11             #+#    #+#             */
/*   Updated: 2024/06/29 13:10:22 by kai11            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

void	print_envvars(bool allow_null)
{
	t_envvar	*envvar;

	envvar = g_info.envmap->envvar_dummy_head.next;
	while (envvar)
	{
		if (envvar->is_exported)
		{
			if (allow_null)
			{
				if (envvar->value)
					printf("declare -x %s=%s\n", envvar->name, envvar->value);
			}
			else
			{
				if (envvar->value)
					printf("%s=%s\n", envvar->name, envvar->value);
			}
			envvar = envvar->next;
		}
	}
}

int	builtin_export(char **argv)
{
	size_t	i;
	char	*name;
	char	*value;

	if (argv[1] == NULL)
	{
		print_envvars(true);
		return (0);
	}
	else
	{
		i = 1;
		while (argv[i])
		{
			map_make(g_info.envmap, argv[i], true);
			i++;
		}
		return (0);
	}
	assert_error("export");
	return (1);
}
