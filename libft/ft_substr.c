/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikelsk <inikelsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 09:55:38 by inikelsk          #+#    #+#             */
/*   Updated: 2025/04/24 14:39:04 by inikelsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Allocate memory and return a substring from the string 's'. The substring
starts at index 'start' and has a maximum length of 'len'. On failure, return
NULL. If start is equal to or greater than s length, return an empty string. 
Note that I explicitly include a '\0', which requires +1 on malloc. */
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	s_len;
	size_t	substr_len;
	size_t	i;
	char	*substr;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		substr_len = 0;
	else if (start + len > s_len)
		substr_len = s_len - start;
	else
		substr_len = len;
	substr = malloc((substr_len + 1) * sizeof(char));
	if (!substr)
		return (NULL);
	i = 0;
	while (i < substr_len)
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}

/* #include <stdio.h>
int	main(void)
{
	char	*s = "Hello, world!";
	char	*sub;

	// Test 1: Normal case
	sub = ft_substr(s, 7, 5);
	printf("Test 1: '%s'\n", sub);
	free(sub);
	// Test 2: start >= strlen(s)
	sub = ft_substr(s, 20, 5);
	printf("Test 2: '%s'\n", sub);
	free(sub);
	// Test 3: len goes past end of string
	sub = ft_substr(s, 10, 10);
	printf("Test 3: '%s'\n", sub);
	free(sub);
	// Test 4: len == 0
	sub = ft_substr(s, 5, 0);
	printf("Test 4: '%s'\n", sub);
	free(sub);
	// Test 5: NULL input
	sub = ft_substr(NULL, 0, 5);
	printf("Test 5: '%s'\n", sub); // Expecting (null) or NULL-safe behavior
	return (0);
} */
