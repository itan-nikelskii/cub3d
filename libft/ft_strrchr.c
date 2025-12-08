/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikelsk <inikelsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 12:51:52 by inikelsk          #+#    #+#             */
/*   Updated: 2025/04/23 13:27:07 by inikelsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Return a pointer to the last occurrence of char c in the string s, or NULL
if the char is not found. The terminating \0 is considered part of the string, 
so if c is specified as '\0', a pointer to the terminator is returned. 

Note that c is casted to char to treat it as an unsigned char (C standard). */
char	*ft_strrchr(const char *s, int c)
{
	char	*result;

	result = NULL;
	while (*s)
	{
		if (*s == (char)c)
			result = (char *)s;
		s++;
	}
	if (*s == (char)c)
		result = (char *)s;
	return (result);
}

/* #include <stdio.h>
int	main(void)
{
	char	*str = "hello";
	char	c = 'l';
	char	*result = ft_strrchr(str, c);

	if (result)
		printf("Found: %s\n", result);
	else
		printf("Character not found.\n");

	return (0);
} */
