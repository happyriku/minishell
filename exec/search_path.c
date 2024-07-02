/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkodaira <kkodaira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 19:54:44 by kkodaira          #+#    #+#             */
/*   Updated: 2024/06/29 20:19:06 by kkodaira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_path(char *path, size_t	pathsize,
	const char *filename, char **envpath)
{
	char	*end;

	bzero(path, pathsize);
	end = strchr(*envpath, ':');
	if (*envpath == end)
		strlcpy(path, ".", pathsize);
	else if (end)
		strncpy(path, *envpath, end - *envpath);
	strlcat(path, "/", pathsize);
	strlcat(path, filename, pathsize);
	if (end == NULL)
		*envpath = NULL;
	else
		*envpath = end + 1;
}

char	*search_path_mode(const char *filename, int mode)
{
	char	path[PATH_MAX];
	char	*envpath;
	char	*dup;

	envpath = get_value_from_name(g_info.envmap, "PATH");
	while (envpath && *envpath)
	{
		set_path(path, PATH_MAX, filename, &envpath);
		if (access(path, mode) == 0)
		{
			dup = strdup(path);
			if (dup == NULL)
				fatal_error("strdup");
			return (dup);
		}
	}
}

char	*search_path(const char *filename)
{
	char	*path;

	//実行権限
	path = search_path_mode(filename, X_OK);
	if (path)
		return (path);
	//ファイルが存在するかどうか
	path = search_path_mode(filename, F_OK);
	return (path);
}
