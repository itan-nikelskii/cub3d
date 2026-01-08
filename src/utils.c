/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgroos <mgroos@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 14:14:58 by inikelsk          #+#    #+#             */
/*   Updated: 2026/01/08 13:02:51 by mgroos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h> // for printf()
#include <unistd.h> // for exit()
#include <stdlib.h> // for free()

/* Print the error message and exit the program. */
void	error_exit(char *msg)
{
	printf("Error: %s\n", msg);
	exit(1);
}

/* Free a 2D array of strings (first iterate through the array freeing every 
string, then free the array pointer itself. */
void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
