/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kai11 <kai11@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 14:24:03 by kai11             #+#    #+#             */
/*   Updated: 2024/06/27 14:29:51 by kai11            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_echo(char **argv)
{
	size_t	i;

	if (argv[1] == NULL)
		printf("\n");
	if (argv[1])
	{
		if (strcmp(argv[1], "-n") == 0)
		{
			if (argv[2] == NULL)
				return (0);
			else
			{
				i = 2;
				while (argv[i] && argv[i + 1])
				{
					printf("%s ", argv[i]);
					i++;
				}
				printf("%s", argv[i]);
			}
		}
		else
		{
			i = 1;
			while (argv[i] && argv[i + 1])
			{
				printf("%s ", argv[i]);
				i++;
			}
			printf("%s\n", argv[i]);
		}
	}
	return (0);
}
