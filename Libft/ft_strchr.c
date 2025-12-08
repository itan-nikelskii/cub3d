/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikelsk <inikelsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 12:22:15 by inikelsk          #+#    #+#             */
/*   Updated: 2025/12/08 10:24:04 by inikelsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Return a pointer to the first occurrence of char c in the string s, or NULL
if the char is not found. The terminating \0 is considered part of the string, 
so if c is specified as '\0', a pointer to the terminator is returned. 

Note that c is casted to char to treat it as an unsigned char (C standard). */
char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	return (NULL);
}

/* #include <stdio.h>
int	main(void)
{
	char	*str = "hello";
	char	c = 'e';
	char	*result = ft_strchr(str, c);

	if (result)
		printf("Found: %s\n", result);
	else
		printf("Character not found.\n");

	return (0);
} */
