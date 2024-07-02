/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kai11 <kai11@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 16:20:25 by kai11             #+#    #+#             */
/*   Updated: 2024/06/30 17:16:48 by kai11            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_argv(char **argv)
{
	size_t	i;

	if (argv == NULL || *argv == NULL)
		return ;
	i = 0;
	while (argv[i] != NULL)
	{
		printf("here\n");
		free(argv[i]);
		printf("end\n");
		i++;
	}
	free(argv);
	argv = NULL;
}
