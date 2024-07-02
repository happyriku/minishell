/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kai11 <kai11@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 14:30:05 by kai11             #+#    #+#             */
/*   Updated: 2024/06/27 14:32:52 by kai11            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int builtin_pwd(char **argv)
{
    char    cwd[PATH_MAX];

    if (getcwd(cwd, PATH_MAX) != NULL)
        printf("%s", cwd);
    else
        return (1);
    return (0);
}
