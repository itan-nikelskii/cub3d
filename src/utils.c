/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgroos <mgroos@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 14:14:58 by inikelsk          #+#    #+#             */
/*   Updated: 2025/12/30 12:29:16 by mgroos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* TODO: documentation; maybe a bool check for whether things need to be freed? */
void	error_exit(char *msg)
{
	printf("Error: %s\n", msg);
	// TODO: free everything here (if it needs to be freed)
	// note manon: i've put cleaning functions before error_exit in the visualisation
	// functions, so if we do free in here we should double-check we're not 
	// freeing twice.
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
