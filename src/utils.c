/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikelsk <inikelsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 14:14:58 by inikelsk          #+#    #+#             */
/*   Updated: 2025/12/08 14:23:10 by inikelsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* TODO: documentation; maybe a bool check for whether things need to be freed? */
void	error_exit(char *msg)
{
	printf("Error: %s\n", msg);
	// TODO: free everything here (if it needs to be freed)
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
