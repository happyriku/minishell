/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kai11 <kai11@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 18:58:35 by kkodaira          #+#    #+#             */
/*   Updated: 2024/06/30 16:39:25 by kai11            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>

int	exec(t_node *node)
{
	pid_t	last_pid;
	int		status;

	if (open_files(node) < 0)
		return (OPEN_FILES_ERROR);
	if (node->next == NULL && is_builtin(node))
		status = exec_builtin(node);
	else
	{
		last_pid = exec_pipeline(node);
		status = wait_pipeline(last_pid);
	}
	return (status);
}

void	validate_access(const char *path, const char *filename)
{
	struct stat	st;

	if (path == NULL)
		err_exit(filename, "command not found", 127);
	if (strcmp(filename, "") == 0)
		err_exit(filename, "command not found", 127);
	if (strcmp(filename, "..") == 0)
		err_exit(filename, "command not found", 127);
	if (access(path, F_OK) < 0)
		err_exit(filename, "command not found", 127);
	if (stat(path, &st) < 0)
		fatal_error("fstat");
	if (S_ISDIR(st.st_mode))
		err_exit(filename, "is a directory", 126);
	if (access(path, X_OK) < 0)
		err_exit(path, "Permission denied", 126);
}

int	exec_nonbuiltin(t_node *node)
{
	char	*path;
	char	**argv;

	do_redirect(node->command->redirects);
	argv = make_argv_from_args(node->command->args);
	path = argv[0];
	if (strchr(path, '/') == NULL)
		path = search_path(path);
	validate_access(path, argv[0]);
	execve(path, argv, get_environ(g_info.envmap));
	free(argv);
	reset_redirect(node->command->redirects);
	fatal_error("execve");
}

pid_t	exec_pipeline(t_node *node)
{
	pid_t	pid;

	if (node == NULL)
		return (-1);
	prepare_pipe(node);
	pid = fork();
	if (pid < 0)
		fatal_error("fork");
	else if (pid == 0)
	{
		reset_signal();
		prepare_pipe_child(node);
		if (is_builtin(node))
			exit(exec_builtin(node));
		else
			exec_nonbuiltin(node);
	}
	prepare_pipe_parent(node);
	if (node->next)
		return (exec_pipeline(node->next));
	return (pid);
}

int	wait_pipeline(pid_t	last_pid)
{
	pid_t	wait_result;
	int		status;
	int		wstatus;

	while (1)
	{
		//子プロセスの終了を待つ、wstatusに終了ステータスが入る
		wait_result = wait(&wstatus);
		if (wait_result == last_pid)
		{
			//プロセスがシグナルで終了
			if (WIFSIGNALED(wstatus))
			//128 + シグナル番号
				status = 128 + WTERMSIG(wstatus);
			else
			//子プロセスの終了ステータス
				status = WEXITSTATUS(wstatus);
		}
		else if (wait_result < 0)
		{
			//待機中の子プロセスがもう存在しない
			if (errno == ECHILD)
				break ;
			//子プロセスがシグナルで終了した
			else if (errno == EINTR)
				continue;
			else
				fatal_error("wait");
		}
	}
	return (status);
}
