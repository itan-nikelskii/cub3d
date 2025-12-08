/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikelsk <inikelsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:52:19 by inikelsk          #+#    #+#             */
/*   Updated: 2025/12/08 13:17:43 by inikelsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Duplicate string s and return the result, or NULL on malloc failure. */
char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*dup;
	size_t	i;

	len = ft_strlen(s);
	dup = malloc(len + 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
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
