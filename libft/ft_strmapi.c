/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikelsk <inikelsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 12:02:48 by inikelsk          #+#    #+#             */
/*   Updated: 2025/04/26 13:18:27 by inikelsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Applies the function f to each character of the string s; f takes the index
of a character as the first argument and the character itself as the second.
Return a new string, created with malloc(), that stores the results from the 
successive applications of f. On allocation failure, return NULL. */
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	len;
	unsigned int	i;
	char			*result;

	if (!s || !f)
		return (NULL);
	len = 0;
	while (s[len])
		len++;
	result = malloc((len + 1) * sizeof(char));
	if (!result)
		return (NULL);
	i = 0;
	while (i < len)
	{
		result[i] = f(i, s[i]);
		i++;
	}
	result[len] = '\0';
	return (result);
}

/* // Put this on top for testing
char	ft_toupper_map(unsigned int i, char c)
{
	(void)i;
	if (c >= 'a' && c <= 'z')
		return (c - ('a' - 'A'));
	return (c);
}
#include <stdio.h>
int	main(void)
{
	char	*s = "123 abcdE";
    char	*new_s = ft_strmapi(s, ft_toupper_map);
    printf("Original: %s\n", s);
    printf("Mapped:   %s\n", new_s);
    free(new_s);
    return (0);
} */
