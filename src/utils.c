/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikelsk <inikelsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 14:14:58 by inikelsk          #+#    #+#             */
/*   Updated: 2026/01/03 18:05:06 by inikelsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
