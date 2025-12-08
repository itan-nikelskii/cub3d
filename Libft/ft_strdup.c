/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikelsk <inikelsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:52:19 by inikelsk          #+#    #+#             */
/*   Updated: 2025/04/29 15:23:10 by inikelsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Duplicate string s and return a pointer to the duplicate. On failure, return
a NULL pointer. Notice (ft_strlen(s) + 1) accounting for the nul-terminator. */
char	*ft_strdup(const char *s)
{
	size_t	total_len;
	char	*duplicate;

	total_len = ft_strlen(s) + 1;
	duplicate = malloc(total_len * sizeof(char));
	if (!duplicate)
	{
		return (NULL);
	}
	(void)ft_strlcpy(duplicate, s, total_len);
	return (duplicate);
}

/* #include <stdio.h>
int	main(void)
{
	const char	*original = "Hello, world!";
	char		*copy = strdup(original);

	if (copy != NULL)
	{
		printf("Original: %s\n", original);
		printf("Copy: %s\n", copy);
		free(copy);
	}
	else
	{
		printf("Memory allocation failed.\n");
	}
	return (0);
} */
