/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kai11 <kai11@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:28:27 by kai11             #+#    #+#             */
/*   Updated: 2024/06/30 17:10:22 by kai11            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	append_path(char **new_path, char **rest, char *path)
{
	while (*path && *path != '/')
	{
		append_char(new_path, *(path++));
	}
	if (*path == '/' && *(path + 1))
		append_char(new_path, *(path++));
	append_char(new_path, '\0');
	*rest = path;
}

void	delete_last_path(char **new_path, char **rest, char *path)
{
	char	*p;
	char	*new;
	size_t	i;

	p = *new_path;
	i = 0;
	while (p[i + 1] != '\0')
		i++;
	if (p[i] == '/')
		i--;
	while (p[i] != '/')
		i--;
	p[i + 2] = '\0';
	new = malloc(sizeof(char) * (i + 2));
	if (new == NULL)
		fatal_error("malloc");
	strlcpy(new, *new_path, i + 2);
	free(*new_path);
	*new_path = new;
	*rest = path + 2;
}

char	*path_interpret(char *path)
{
	char	*p;
	char	*pre;
	char	*new_path;
	size_t	i;

	p = path;
	new_path = calloc(1, sizeof(char));
	if (new_path == NULL)
		fatal_error("calloc");
	if (*path == '/')
	{
		pre = malloc(sizeof(char) * 2);
		if (pre == NULL)
			fatal_error("malloc");
		pre[0] = '/';
		pre[1] = '\0';
	}
	else
		pre = get_value_from_name(g_info.envmap, "PWD");
	i = 0;
	while (pre[i])
	{
		append_char(&new_path, pre[i]);
		i++;
	}
	if (pre)
		free(pre);
	while (*path)
	{
		if (*path == '/')
			path++;
		else if (strncmp(path, "..", 2) == 0)
			delete_last_path(&new_path, &path, path);
		else
			append_path(&new_path, &path, path);
	}
	free(p);
	return (new_path);
}

void	oldpwd_update(t_envmap *map, char *new_value)
{
	t_envvar	*cur;

	cur = map->envvar_dummy_head.next;
	while (cur)
	{
		if (strncmp(cur->name, "OLDPWD", strlen(cur->name)) == 0)
			break ;
		cur = cur->next;
	}
	if (cur == NULL)
		assert_error("oldpwd_update");
	if (cur->value)
		free(cur->value);
	if (new_value)
		cur->value = new_value;
	else
		cur->value = NULL;
}

void	pwd_update(t_envmap *map, char *value)
{
	t_envvar	*cur;

	cur = map->envvar_dummy_head.next;
	while (cur)
	{
		if (strncmp(cur->name, "PWD", strlen(cur->name)) == 0)
			break ;
		cur = cur->next;
	}
	if (cur == NULL)
		assert_error("pwd_update");
	if (cur->value)
		free(cur->value);
	if (value)
		cur->value = value;
	else
		cur->value = NULL;
}

int	builtin_cd(char **argv)
{
	char	*new_path;

	if (argv[1] != NULL && argv[2] != NULL)
	{
		syntax_error("builtin cd1");
		return (1);
	}
	if (argv[1] == NULL)
	{
		new_path = get_value_from_name(g_info.envmap, "HOME");
		if (chdir(new_path) < 0)
		{
			syntax_error("chdir");
			return (1);
		}
		oldpwd_update(g_info.envmap,
			get_value_from_name(g_info.envmap, "PWD"));
		pwd_update(g_info.envmap, new_path);
		return (0);
	}
	else
	{
		new_path = path_interpret(argv[1]);
		if (chdir(new_path) < 0)
		{
			syntax_error("chdir");
			return (1);
		}
	}
	oldpwd_update(g_info.envmap,
		get_value_from_name(g_info.envmap, "PWD"));
	pwd_update(g_info.envmap, new_path);
	return (0);
}
