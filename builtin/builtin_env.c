/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kai11 <kai11@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:23:51 by kai11             #+#    #+#             */
/*   Updated: 2024/06/27 13:28:10 by kai11            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int builtin_env(char **argv)
{
    char cwd[PATH_MAX];

    print_envvars(false);
    if (getcwd(cwd, PATH_MAX) != NULL)
        printf("'_'=%s\n");
    else
        return (1);
    return (0);
}