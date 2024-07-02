/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rishibas <rishibas@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 11:56:22 by kai11             #+#    #+#             */
/*   Updated: 2024/07/01 16:12:14 by rishibas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>

bool    is_builtin(t_node *node)
{
    char *cmd_name;

    cmd_name = node->command->args->word;
    if (strcmp(cmd_name, "exit") == 0)
        return (true);
    else if (strcmp(cmd_name, "export") == 0)
        return (true);
    else if (strcmp(cmd_name, "unset") == 0)
        return (true);
    else if (strcmp(cmd_name, "env") == 0)
        return (true);
    else if (strcmp(cmd_name, "cd") == 0)
        return (true);
    else if (strcmp(cmd_name, "echo") == 0)
        return (true);
    else if (strcmp(cmd_name, "pwd") == 0)
        return (true);
    return (false);
}

size_t  get_size(t_token *args)
{
    size_t size;

    while (args && args->kind != TK_EOF)
    {
        size++;
        args = args->next;
    }
    return (size);
}

char    **make_argv_from_args(t_token *args)
{
    char    **argv;
    size_t  size;
    size_t  i;

    size = get_size(args);
    argv = malloc(sizeof(char *) * (size + 1));
    if (argv == NULL)
        fatal_error("malloc");
    i = 0;
    while (args && args->kind != TK_EOF)
    {
        argv[i] = malloc(sizeof(char) * (strlen(args->word) + 1));
        if (argv[i] == NULL)
            fatal_error("malloc");
        strlcat(argv[i], args->word, strlen(args->word) + 1);
        i++;
        args = args->next;
    }
    return (argv);
}

int exec_builtin(t_node *node)
{
    char **argv;
    int  status;

    argv = make_argv_from_args(node->command->args);
    if (strcmp(argv[0], "exit") == 0)
        status = builtin_exit(argv);
    else if (strcmp(argv[0], "export") == 0)
        status = builtin_export(argv);
    else if (strcmp(argv[0], "unset") == 0)
        status = builtin_unset(argv);
    else if (strcmp(argv[0], "env") == 0)
        status = builtin_env(argv);
    else if (strcmp(argv[0], "cd") == 0)
        status = builtin_cd(argv);
    else if (strcmp(argv[0], "echo") == 0)
        status = builtin_echo(argv);
    else if (strcmp(argv[0], "pwd") == 0)
        status = builtin_pwd(argv);
    else 
        assert_error("exec builtin");
    return (status);
}
