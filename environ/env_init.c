/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkodaira <kkodaira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 13:01:32 by kai11             #+#    #+#             */
/*   Updated: 2024/06/25 20:15:17 by kkodaira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	envmap_init(t_envmap *envmap, char **environ)
{
	size_t		i;
	char		cwd[PATH_MAX];

	i = 0;
	while (environ[i])
	{
		map_make(envmap, environ[i], false);
		i++; 
	}
	if (get_value_from_name(envmap, "SHLVL") == NULL)
		map_set(envmap, "SHLVL", "1");
	if (get_value_from_name(envmap, "PWD") == NULL)
	{
		getcwd(cwd, PATH_MAX);
		map_set(envmap, "PWD", cwd);
	}
	map_set(envmap, "OLDPWD", NULL);
}

void	env_init(void)
{
	extern char	**environ;

	g_info.envmap = calloc(1, sizeof(t_envmap));
	if (g_info.envmap == NULL)
		fatal_error("calloc");
	envmap_init(g_info.envmap, environ);
}
