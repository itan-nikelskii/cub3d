/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikelsk <inikelsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:39:27 by inikelsk          #+#    #+#             */
/*   Updated: 2025/04/30 14:51:34 by inikelsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Locate the first occurrence of the null-terminated string 'little' in the
string 'big'; not more than len characters are searched. Characters that appear
after ‘\0’ are not cmpared.
If little is an empty string, big is returned; if little occurs nowhere in big,
NULL is returned; otherwise a pointer to the first char of the first occurrence
of little is returned. */
char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	little_len;

	little_len = ft_strlen(little);
	if (little_len == 0)
		return ((char *)big);
	i = 0;
	while (big[i] && little_len + i <= len)
	{
		j = 0;
		while (big[i + j] && j < little_len && big[i + j] == little[j])
			j++;
		if (j == little_len)
			return ((char *)(big + i));
		i++;
	}
	return (NULL);
}

/* #include <stdio.h> 
int	main(void)
{
	char	*str = "These aren't the droids you're looking for.";
	char	*to_find = "droids";
	char	*result = ft_strnstr(str, to_find, 44);

	if (result == NULL)
	{
		printf("Substring not found\n");
	}
	else
	{
		printf("%s\n", result);
	}
	return (0);
} */
